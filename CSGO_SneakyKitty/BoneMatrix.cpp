#include "BoneMatrix.h"
#include "Position.h"


BoneMatrix::operator Position() const
{
    return Position(this->x_, this->y_, this->z_);
}

/*



Bone Bone::bone_list[client::MAX_PLAYER][Bone::MAX_BONE];


void Bone::UpdateEntityBones()
{
	while (true)
	{
		if (client::connection_status != client::ConnectionState::FULLY_CONNECTED)
		{
			Sleep(5000);
			continue;
		}

		for (int entity_index = 0; entity_index < client::MAX_PLAYER; ++entity_index)
		{
			if (PlayerEntity::player_entity_list[entity_index].team == PlayerEntity::Team::INVALID) continue;

			DWORD bone_matrix_address;
			rM(PlayerEntityAddress::player_entity_address_list[entity_index].entity_address + m_dwBoneMatrix, bone_matrix_address);

			ReadProcessMemory(module::csgo_handle, reinterpret_cast<LPCVOID>(bone_matrix_address + sizeof(Bone) * Bone::DefinitionIndex::SPINE), bone_list[entity_index], sizeof(bone_list[entity_index]), NULL);

			//increase head's center height a little bit
			bone_list[entity_index][3].z += 1.0f;
		}

		this_thread::sleep_for(chrono::milliseconds(1));
	}
}


*/