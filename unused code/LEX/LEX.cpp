#include <kamek.hpp>


namespace OptPack {
namespace LEX {

void OpenLEX() {
    lex_ptr = open_szs_subfile(file_open_data_addr, 1, "course.lex", 0); // call to 805411fc
    lex_file_reset();
    lex_file_parse();
    set_online_time_limit_by_lex(lex_set1_data.apply_online_sec);
}
kmCall(0x80512820, OpenLEX);

void lex_file_parse()
{
    if ( !lex_ptr || isModeWorldwide() )
        return;

    if (lex_ptr->magic != 0x4c452d58) {
        LEReport("This is not a valid course.lex file\n");
        return;
    }

    if (lex_ptr->major_version != 1) {
        LEReport("course.lex file has invalid version (%d), need %d\n", lex_ptr->major_version, 1);
        return;
    }

    lex_element_t * lex_element_ptr = (lex_element_t *)((int)((int)lex_ptr + (int)lex_ptr->element_off));

    void * object_data_ptr;

    while (lex_element_ptr->magic != 0)
    {
        object_data_ptr = (void *)((int)lex_element_ptr + 8);

        switch (lex_element_ptr->magic)
        {
            case 0x43414e4e: // "CANN": Cannon settings.
                // object data ptr contains offset to cannon data
                // The game stores cannon speeds in a float[4] for each cannon type which is at PAL 808b5ce8.
                // This array is loaded / used at PAL 805850a4, in a set of lis/addi instructions. 
                // We're just patching these, so cannon data is loaded from the temporary LEX buffer instead.
                object_data_ptr = (void *)(((int)object_data_ptr) + 4); // skip size
                code_patcher(&mkwfun_lex_cannon_type_patch_addr, 0, 0x3c600000 + (((unsigned int)object_data_ptr >> 16) & 0xffff));
                code_patcher(&mkwfun_lex_cannon_type_patch_addr, 4, 0x60630000 + ((unsigned int)object_data_ptr & 0xffff));
                break;

            case 0x48495054: // "HIPT": HIde Position Tracker
                lex_hipt_len = lex_element_ptr->size / sizeof(*lex_hipt_list);
                lex_hipt_list = object_data_ptr;
                LEDebugReport("XPF: load LEX/HIPT, size=%d -> n=%d\n", lex_element_ptr->size, lex_hipt_len);
                break;

            case 0x52495450: // "RITP": Random ITem Points
                lex_ritp_len = lex_element_ptr->size / sizeof(*lex_ritp_list);
                lex_ritp_list = object_data_ptr;
                LEDebugReport("XPF: load LEX/RITP, size=%d -> n=%d\n", lex_element_ptr->size, lex_ritp_len);
                break;


            case 0x53455431: // "SET1": Settings #1
		{
		    unsigned size = lex_element_ptr->size;
		    LEDebugReport("load LEX/SET1, size=%d, max-size=%d\n",
				size, sizeof(lex_set1_t));
		    if (size > sizeof(lex_set1_t))
			size = sizeof(lex_set1_t);
		    memcpy(&lex_set1_data, object_data_ptr, size);
		 }
		 break;

            case 0x54455354: // "TEST": Settings to tests.
		{
		    unsigned size = lex_element_ptr->size;
		    LEDebugReport("XPF: load LEX/TEST, size=%d, max-size=%d\n", size, sizeof(lex_test_t));
		    if (size > sizeof(lex_test_t))
			size = sizeof(lex_test_t);
		    memcpy(&lex_test_data, object_data_ptr, size);
		}
		break;

            // case 0x2d2d2d2d:	// "----", invalidated section, ignore.
            default: // ignore unknown sections
                break;
        }

        // go to next element:
        lex_element_ptr = (lex_element_t *)((int)lex_element_ptr + lex_element_ptr->size + 8);
    }

    lex_ptr = 0;
}

const lex_dev1_t lex_dev1_data_reset = { 0 };
const lex_set1_t lex_set1_data_reset = { { 1.0, 1.0, 1.0 }, 0, 0, 0 };
const lex_test_t lex_test_data_reset = { 0, 0, 0, -1, 0, 0 };

void lex_file_reset()
{
        // reset cannon param (PAL 805850a4)
        #if REGION_LETTER == 'P'
            code_patcher(&mkwfun_lex_cannon_type_patch_addr, 0, 0x3c60808b);
            code_patcher(&mkwfun_lex_cannon_type_patch_addr, 4, 0x38635ce8);
        #elif REGION_LETTER == 'E'
            code_patcher(&mkwfun_lex_cannon_type_patch_addr, 0, 0x3c60808b);
            code_patcher(&mkwfun_lex_cannon_type_patch_addr, 4, 0x38631428);
        #elif REGION_LETTER == 'J'
            code_patcher(&mkwfun_lex_cannon_type_patch_addr, 0, 0x3c60808b);
            code_patcher(&mkwfun_lex_cannon_type_patch_addr, 4, 0x38634e48);
        #elif REGION_LETTER == 'K'
            code_patcher(&mkwfun_lex_cannon_type_patch_addr, 0, 0x3c60808a);
            code_patcher(&mkwfun_lex_cannon_type_patch_addr, 4, 0x38634160);
        #else
            #error "no region"
        #endif

            // reset LEX data
        // [[lex-dev]]
            lex_dev1_data = lex_dev1_data_reset;
            lex_set1_data = lex_set1_data_reset;
            lex_test_data = lex_test_data_reset;
            lex_hipt_len = 0;
            lex_ritp_len = 0;
            *lex_ritp_log = 0;
}


//
asmFunc ITEMPOS() {
    ASM(
        nofralloc;
.extern lex_set1_data;
.globl itemrange_receive_X_mod

itemrange_receive_X_mod: 
    lis r5, lex_set1_data@ha;
    lfs f1, lex_set1_data@l(r5);	// load factor
    fmuls f0, f0, f1;			// multiply f0 with factor
    stfs f0, 0(r4);			// store new value
    blr; 

.globl itemrange_send_X_mod
itemrange_send_X_mod:
    lis r5, lex_set1_data@ha;
    lfs f1, lex_set1_data@l(r5);	// load factor
    lfs f0, 0(r4);			// load original value to send
    fdivs f0, f0, f1;			// divide by factor
    blr; 

.globl itemrange_receive_Y_mod
itemrange_receive_Y_mod: 
    lis r5, (lex_set1_data+4)@ha;
    lfs f1, (lex_set1_data+4)@l(r5);	// load factor
    fmuls f0, f0, f1;			// multiply f0 with factor
    stfs f0, 0(r4);			// store new value
    blr; 
    
.globl itemrange_send_Y_mod
itemrange_send_Y_mod:
    lis r5, (lex_set1_data+4)@ha;
    lfs f1, (lex_set1_data+4)@l(r5);	// load factor
    lfs f0, 0(r4);			// load original value to send
    fdivs f0, f0, f1;			// divide by factor
    blr; 
    
    
.globl itemrange_receive_Z_mod
itemrange_receive_Z_mod: 
    lis r5, (lex_set1_data+8)@ha;
    lfs f1, (lex_set1_data+8)@l(r5);	// load factor
    fmuls f0, f0, f1;			// multiply f0 with factor
    stfs f0, 0(r4);			// store new value
    blr; 
  
.globl itemrange_send_Z_mod
itemrange_send_Z_mod:
    lis r5, (lex_set1_data+8)@ha;
    lfs f1, (lex_set1_data+8)@l(r5);	// load factor
    lfs f0, 0(r4);			// load original value to send
    fdivs f0, f0, f1;			// divide by factor
    blr;
    )
}
kmCall(, ITEMPOS);
  // fix for receiving items:
    // shot_drop is at PAL 0x8079b4ac
    code_patcher_BL(&EVENTDATA_item_position_SHOT_DROP, 0x1ac, &itemrange_receive_X_mod); // X
    code_patcher_BL(&EVENTDATA_item_position_SHOT_DROP, 0x2b0, &itemrange_receive_Y_mod); // Y
    code_patcher_BL(&EVENTDATA_item_position_SHOT_DROP, 0x3b0, &itemrange_receive_Z_mod); // Z

    // tail_destroy is at PAL 0x8079c960
    code_patcher_BL(&EVENTDATA_item_position_TAIL_DESTROY, 0x1ac, &itemrange_receive_X_mod); // X
    code_patcher_BL(&EVENTDATA_item_position_TAIL_DESTROY, 0x2b0, &itemrange_receive_Y_mod); // Y
    code_patcher_BL(&EVENTDATA_item_position_TAIL_DESTROY, 0x3b0, &itemrange_receive_Z_mod); // Z


    // fix for sending items:
    code_patcher_BL(&EVENTDATA_item_position_SHOT_DROP, 0x13c, &itemrange_send_X_mod); // X
    code_patcher_BL(&EVENTDATA_item_position_SHOT_DROP, 0x23c, &itemrange_send_Y_mod); // Y
    code_patcher_BL(&EVENTDATA_item_position_SHOT_DROP, 0x33c, &itemrange_send_Z_mod); // Z

    code_patcher_BL(&EVENTDATA_item_position_TAIL_DESTROY, 0x13c, &itemrange_send_X_mod); // X
    code_patcher_BL(&EVENTDATA_item_position_TAIL_DESTROY, 0x23c, &itemrange_send_Y_mod); // Y
    code_patcher_BL(&EVENTDATA_item_position_TAIL_DESTROY, 0x33c, &itemrange_send_Z_mod); // Z


   // Convert to milliseconds and split to hi and lo word
    const unsigned int time = seconds * 1000;
    const unsigned short hi = (time >> 16) & 0xffff;
    const unsigned short lo = (time & 0xffff);

    // Create ASM instructions
    const unsigned int asm_hi = 0x3c600000 | hi; // lis r3, time@h;
    const unsigned int asm_lo = 0x60640000 | lo; // ori r4, r3, time@l;

    // Patch
    code_patcher(&mod_online_time_limit_addr, 0, asm_hi);
    code_patcher(&mod_online_time_limit_addr, 4, asm_lo);

}// namespace LEX
}// namespace OptPack