#pragma once

#include "packet_reader.hpp"

#include <string>

namespace maplestory
{
	/* GW_CharacterStat */
	typedef struct _character_info
	{
		unsigned int id;
		std::string name;

		unsigned char gender;		// 01 == female
		unsigned char skin;
		unsigned int face;
		unsigned int hair;

		unsigned char level;
		unsigned short job_id;

		unsigned short stat_str;
		unsigned short stat_dex;
		unsigned short stat_int;
		unsigned short stat_luk;

		unsigned int stat_hp;
		unsigned int stat_maxhp;

		unsigned int stat_mp;
		unsigned int stat_maxmp;

		unsigned short ability_points;

		unsigned char job_level;
		unsigned int skill_points;

		unsigned __int64 stat_exp;
		unsigned int fame;
		unsigned int gachapon_xp;
		unsigned __int64 stat_temp_exp;

		unsigned int map_id;
		unsigned char portal;

		void decode(packet_reader& packet)
		{
			char character_name[14];
			memset(character_name, 0, sizeof(character_name));

			this->id = packet.read_dword();

			packet.read_buffer(reinterpret_cast<unsigned char*>(character_name), 13);
			this->name = std::string(character_name);

			this->gender = packet.read_byte();
			this->skin = packet.read_byte();
			this->face = packet.read_dword();
			this->hair = packet.read_dword();
		
			packet.read_byte();
			packet.read_byte();
			packet.read_byte();
			
			this->level = packet.read_byte();
			this->job_id = packet.read_word();
			
			this->stat_str = packet.read_word();
			this->stat_dex = packet.read_word();
			this->stat_int = packet.read_word();
			this->stat_luk = packet.read_word();

			this->stat_hp = packet.read_dword();
			this->stat_maxhp = packet.read_dword();

			this->stat_mp = packet.read_dword();
			this->stat_maxmp = packet.read_dword();

			this->ability_points = packet.read_word();
		
			if (this->is_correct_job())
			{
				this->skill_points = 0;
				unsigned char skill_point_sets = packet.read_byte();

				for (unsigned char i = 0; i < skill_point_sets; i++)
				{
					this->job_level = packet.read_byte();
					this->skill_points = packet.read_dword();
				}
			}
			else
			{
				this->skill_points = packet.read_word();
			}

			this->stat_exp = packet.read_qword();
			this->fame = packet.read_dword();
			this->gachapon_xp = packet.read_dword();
			this->stat_temp_exp = packet.read_qword();
		
			packet.read_qword();

			this->map_id = packet.read_dword();
			this->portal = packet.read_byte();

			/* no idea what the rest is */
			packet.read_word();
		
			if (((this->job_id / 100) == 31) || (this->job_id == 3001) || ((this->job_id / 100) == 36) || 
				(this->job_id == 3002) ||	((this->job_id / 100) == 112) || (this->job_id == 11000))
			{
				packet.read_dword();
			}

			packet.read_byte();
			packet.read_dword();
		
			packet.read_dword();
			packet.read_dword();
			packet.read_dword();
			packet.read_dword();
			packet.read_dword();
			packet.read_dword();

			packet.indent(21);
		
			packet.read_dword();
			packet.read_byte();
			packet.read_dword();
			packet.read_byte();
			packet.read_byte();
			packet.read_dword();
			packet.read_byte();
			packet.read_dword();
			packet.read_dword();
			packet.read_dword();
			packet.read_byte();
		
			for (int i = 0; i < 9; i++)
			{
				packet.read_dword();
				packet.read_byte();
				packet.read_dword();
			}

			packet.read_dword();
			packet.read_dword();
			packet.read_dword();
		}

	private:
		bool is_correct_job()
		{
			if (!this->job_id)
			{
				return true;
			}

			if (this->job_id == 100 || this->job_id == 110 || this->job_id == 111 || this->job_id == 112 || this->job_id == 120 || this->job_id == 121 || this->job_id == 122 || this->job_id == 130 || this->job_id == 131 || this->job_id == 132)
			{
				return true;
			}

			if (this->job_id == 200 || this->job_id == 210 || this->job_id == 211 || this->job_id == 212 || this->job_id == 220 || this->job_id == 221 || this->job_id == 222 || this->job_id == 230 || this->job_id == 231 || this->job_id == 232)
			{
				return true;
			}

			if (this->job_id == 300 || this->job_id == 310 || this->job_id == 311 || this->job_id == 312 || this->job_id == 320 || this->job_id == 321 || this->job_id == 322)
			{
				return true;
			}
		  
			if (this->job_id == 400 || this->job_id == 420 || this->job_id == 421 || this->job_id == 422 || this->job_id == 410 || this->job_id == 411 || this->job_id == 412 || this->job_id / 10 == 43)
			{
				return true;
			}

			if (this->job_id == 500 || this->job_id == 510 || this->job_id == 511 || this->job_id == 512 || this->job_id == 520 || this->job_id == 521 || this->job_id == 522 || this->job_id / 10 == 53 || this->job_id == 501 || this->job_id / 10 == 57 || this->job_id == 508)
			{
				return true;
			}

			if (this->job_id / 1000 == 1 || this->job_id / 1000 == 3 || this->job_id / 1000 == 4 || this->job_id / 1000 == 5 || this->job_id / 1000 == 6)
			{
				return true;
			}
		
			if (this->job_id / 100 == 21 || this->job_id == 2000 || this->job_id / 100 == 22 || this->job_id == 2001 ||
				this->job_id / 100 == 23 || this->job_id == 2002 ||	this->job_id / 100 == 24 || this->job_id == 2003 ||
				this->job_id / 100 == 27 || this->job_id == 2004 ||	this->job_id / 100 == 25 || this->job_id == 2005)
			{
				return true;
			}
		
			if (this->job_id == 10000 || this->job_id == 10100 || this->job_id == 10110 || this->job_id == 10111 || this->job_id == 10112)
			{
				return true;
			}

			return false;
		}
	} character_info;
	
	/* AvatarLook */
	typedef struct _character_look
	{
		unsigned char gender;
		unsigned char skin;
		unsigned int face;
		unsigned int job_id;
		unsigned int hair;

		void decode(packet_reader& packet)
		{
			unsigned char position = 0;

			this->gender = packet.read_byte();
			this->skin = packet.read_byte();
			this->face = packet.read_dword();
			this->job_id = packet.read_dword();
			packet.read_byte();					// even MapleStory ignores this value
			this->hair = packet.read_dword();

			position = packet.read_byte();

			while (position != 0xFF)
			{
				packet.read_dword();
				position = packet.read_byte();
			}
		
			position = packet.read_byte();

			while (position != 0xFF)
			{
				packet.read_dword();
				position = packet.read_byte();
			}
		
			packet.indent(27);
		}
	} character_look;
}