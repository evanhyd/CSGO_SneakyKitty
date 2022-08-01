#include "GlowESP.h"


void GlowESP::AdjustAmbientBrightness(float brightness)
{
    //fk valve
    DWORD ambient;
    memory::ReadMem(module::csgo_proc_handle, module::engine_dll + offsets::model_ambient_min - 0x2c, ambient);
    const DWORD encrypted_brightness = *reinterpret_cast<DWORD*>(&brightness) ^ ambient;
    memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::model_ambient_min, encrypted_brightness);
}

bool GlowESP::OnDisable()
{
    if (is_glow_forced_)
    {
        memory::WriteMem(module::csgo_proc_handle, module::client_dll + offsets::force_update_spectator_glow, uint8_t(0x74));
        is_glow_forced_ = false;
    }

    if (is_bright_)
    {
        this->AdjustAmbientBrightness(0.8f);
        is_bright_ = false;
    }

    return false;
}

bool GlowESP::OnExecute()
{
    //avoid race condition
    const int glow_style = user_interface::toggle_mode[user_interface::kGlowESP] - 1;
    if (glow_style < 0) return false;


    //adjust in-game brightness
    if (glow_style == Glow::kFullBody)
    {
        if (!is_bright_)
        {
            this->AdjustAmbientBrightness(1.5f);
            is_bright_ = true;
        }
    }
    else
    {
        if (is_bright_)
        {
            this->AdjustAmbientBrightness(1.0f);
            is_bright_ = false;
        }
    }

    //setup sticky glow
    //0xeb non filck, 0x74 original
    if (!is_glow_forced_)
    {
        memory::WriteMem(module::csgo_proc_handle, module::client_dll + offsets::force_update_spectator_glow, uint8_t(0xeb));
        is_glow_forced_ = true;
    }


    //get the address of GlowObjectManager and the size of the glow array
    DWORD glow_manager[4] = {};
    memory::ReadMem(module::csgo_proc_handle, module::client_dll + offsets::dwGlowObjectManager, glow_manager);


    //predict the glow object list size
    glow_list_.resize(glow_manager[3]);


    //read all the glow object at once
    memory::ReadMem(module::csgo_proc_handle, glow_manager[0], glow_list_.front(), sizeof(Glow) * glow_list_.size());


    //find the corresponding glow ID for each enemy
    for (int entity_id = 0; entity_id < game::kMaxPlayerNum; ++entity_id)
    {
        if (!game::player_is_valid[entity_id]) continue;

        for (int glow_id = 0; glow_id < static_cast<int>(glow_manager[3]); ++glow_id)
        {
            if (glow_list_[glow_id].GetAddress() != game::player_address_list[entity_id].GetAddress()) continue;

            //global target mode or enemy
            if (user_interface::toggle_mode[user_interface::kGlobalTarget] == 1 || game::player_list[game::local_player_index].IsEnemy(game::player_list[entity_id]))
            {
                glow_list_[glow_id].SetGlow(glow_style, game::player_list[entity_id].GetHealth());
                memory::WriteMem(module::csgo_proc_handle, game::player_address_list[entity_id].GetAddress() + offsets::m_clrRender, kEnemyColor);
            }
            else
            {
                glow_list_[glow_id].SetGlow(glow_style, 0.0f, 0.0f, 0.0f, 0.0f, false, false);
                memory::WriteMem(module::csgo_proc_handle, game::player_address_list[entity_id].GetAddress() + offsets::m_clrRender, kTransparent);
            }

            memory::WriteMem(module::csgo_proc_handle, glow_manager[0] + sizeof(Glow) * glow_id, glow_list_[glow_id]);
            break;
        }
    }

    return false;
}