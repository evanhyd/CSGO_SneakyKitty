#include "GlowESP.h"

#include "game.h"
#include "module.h"
#include "offsets.h"
#include "memory.h"
#include "Glow.h"
#include "Cham.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

[[maybe_unused]]
void GlowESP::AdjustAmbientBrightness(float brightness)
{
    //fk valve
    DWORD ambient;
    memory::ReadMem(module::csgo_proc_handle, module::engine_dll + offsets::model_ambient_min - 0x2c, ambient);
    DWORD encrypted_brightness = *reinterpret_cast<DWORD*>(&brightness) ^ ambient;
    memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::model_ambient_min, encrypted_brightness);
}

void GlowESP::operator()(int update_period_ms, [[maybe_unused]]float brightness, Cham enemy_model_color)
{
    constexpr Cham kTransparent(255, 255, 255, 255);

    bool is_glow_forced = false;
    bool is_bright = false;
    std::vector<Glow> glow_list;
    DWORD glow_manager[4] = {};

    while (true)
    {
        //avoid race condition
        const int glow_mode = game::toggle_mode[game::glow_esp_hotkey];

        if (game::connection_state != client::kFullyConnected || glow_mode == 0)
        {
            if (is_glow_forced || is_bright)
            {
                memory::WriteMem(module::csgo_proc_handle, module::client_dll + offsets::force_update_spectator_glow, uint8_t(0x74));
                this->AdjustAmbientBrightness(1.0f);
                is_glow_forced = false;
                is_bright = false;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }


        const int glow_style = glow_mode - 1;
        if (glow_style == Glow::kFullBody)
        {
            if (!is_bright)
            {
                this->AdjustAmbientBrightness(brightness);
                is_bright = true;
            }
        }
        else
        {
            if (is_bright)
            {
                this->AdjustAmbientBrightness(1.0f);
                is_bright = false;
            }
        }

        //0xeb non filck, 0x74 original
        if (!is_glow_forced)
        {
            memory::WriteMem(module::csgo_proc_handle, module::client_dll + offsets::force_update_spectator_glow, uint8_t(0xeb));
            is_glow_forced = true;
        }


        //get the address of GlowObjectManager and the size of the glow array
        memory::ReadMem(module::csgo_proc_handle, module::client_dll + offsets::dwGlowObjectManager, glow_manager);


        //predict the glow object list size
        glow_list.resize(glow_manager[3]);


        //read all the glow object at once
        memory::ReadMem(module::csgo_proc_handle, glow_manager[0], glow_list.front(), sizeof(Glow) * glow_list.size());


        for (int entity_id = 0; entity_id < client::kMaxPlayerNum; ++entity_id)
        {
            if (!game::player_entity_is_valid[entity_id]) continue;

            for (int glow_id = 0; glow_id < static_cast<int>(glow_manager[3]); ++glow_id)
            {
                if (glow_list[glow_id].GetAddress() != game::player_entity_address_list[entity_id].GetAddress()) continue;

                //global target mode or enemy
                if (game::toggle_mode[game::global_target_hotkey] == 1 || game::player_entity_list[game::local_player_index].IsEnemy(game::player_entity_list[entity_id]))
                {
                    glow_list[glow_id].SetGlow(glow_style, game::player_entity_list[entity_id].GetHealth());
                    memory::WriteMem(module::csgo_proc_handle, game::player_entity_address_list[entity_id].GetAddress() + offsets::m_clrRender, enemy_model_color);
                }
                else
                {
                    glow_list[glow_id].SetGlow(glow_style, 0.0f, 0.0f, 0.0f, 0.0f, false, false);
                    memory::WriteMem(module::csgo_proc_handle, game::player_entity_address_list[entity_id].GetAddress() + offsets::m_clrRender, kTransparent);
                }

                memory::WriteMem(module::csgo_proc_handle, glow_manager[0] + sizeof(Glow) * glow_id, glow_list[glow_id]);
                break;
            }
        }


        //this method is faster but unstable, because other objects change consistently
        //WriteProcessMemory(csgo_handle, reinterpret_cast<LPVOID>(pGlowObjectManager[0]), &glowArray[0], sizeof(Glow)* glowArray.size(), NULL);

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}