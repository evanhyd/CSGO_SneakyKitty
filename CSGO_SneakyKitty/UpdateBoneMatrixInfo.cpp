#include "UpdateBoneMatrixInfo.h"

bool UpdateBoneMatrixInfo::OnExecute()
{
    for (int entity_id = 0; entity_id < game::kMaxPlayerNum; ++entity_id)
    {
        if (!game::player_is_valid[entity_id]) continue;

        //obtain the bone matrix struct entry
        DWORD bone_matrix_struct_entry;
        memory::ReadMem(module::csgo_proc_handle, game::player_address_list[entity_id].GetAddress() + offsets::m_dwBoneMatrix, bone_matrix_struct_entry);

        //read the bone matrix starting from spine
        memory::ReadMem(module::csgo_proc_handle, bone_matrix_struct_entry + sizeof(BoneMatrix) * BoneMatrix::kBoneBegin, game::bone_matrix_list[entity_id][BoneMatrix::kBoneBegin], sizeof(BoneMatrix) * BoneMatrix::kUsefulBoneNum);

        //adjust skull position
        game::bone_matrix_list[entity_id][BoneMatrix::kHead].z_ += 1.0f;
    }

    return false;
}