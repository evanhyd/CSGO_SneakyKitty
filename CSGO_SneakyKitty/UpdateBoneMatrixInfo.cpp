#include "UpdateBoneMatrixInfo.h"

#include "game.h"
#include "module.h"
#include "offsets.h"
#include "memory.h"

#include <iostream>
#include <thread>
#include <chrono>

void UpdateBoneMatrixInfo::operator()(int update_period_ms)
{
    while (true)
    {
        if (game::connection_state != client::kFullyConnected)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }


        for (int i = 0; i < client::kMaxPlayerNum; ++i)
        {
            if (!game::player_entity_is_valid[i]) continue;

            //obtain the bone matrix struct entry
            DWORD bone_matrix_struct_entry;
            memory::ReadMem(module::csgo_proc_handle, game::player_entity_address_list[i].GetAddress() + offsets::m_dwBoneMatrix, bone_matrix_struct_entry);

            //read the bone matrix starting from spine
            memory::ReadMem(module::csgo_proc_handle, bone_matrix_struct_entry + sizeof(BoneMatrix) * BoneMatrix::kBoneBegin, game::bone_matrix_list[i][BoneMatrix::kBoneBegin], sizeof(BoneMatrix) * BoneMatrix::kUsefulBoneNum);

            //adjust skull position
            game::bone_matrix_list[i][BoneMatrix::kHead].z_ += 1.0f;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}