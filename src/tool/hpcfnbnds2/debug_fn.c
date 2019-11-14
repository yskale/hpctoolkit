/*  debug.c -- print out various elements of the data structures */

#include	"fnbounds.h"

void
print_elf_header64(Elf64_Ehdr *elf_header)
{

	fprintf(stderr, "========================================\n");
	fprintf(stderr, "\t\tELF Header\n");

	/* Storage capacity class */
	fprintf(stderr, "Storage class\t= ");
	switch(elf_header->e_ident[EI_CLASS])
	{
		case ELFCLASS32:
			fprintf(stderr, "32-bit objects\n");
			break;

		case ELFCLASS64:
			fprintf(stderr, "64-bit objects\n");
			break;

		default:
			fprintf(stderr, "INVALID CLASS\n");
			break;
	}

	/* Data Format */
	fprintf(stderr, "Data format\t= ");
	switch(elf_header->e_ident[EI_DATA])
	{
		case ELFDATA2LSB:
			fprintf(stderr, "2's complement, little endian\n");
			break;

		case ELFDATA2MSB:
			fprintf(stderr, "2's complement, big endian\n");
			break;

		default:
			fprintf(stderr, "INVALID Format\n");
			break;
	}

	/* OS ABI */
	fprintf(stderr, "OS ABI\t\t= ");
	switch(elf_header->e_ident[EI_OSABI])
	{
		case ELFOSABI_SYSV:
			fprintf(stderr, "UNIX System V ABI\n");
			break;

		case ELFOSABI_HPUX:
			fprintf(stderr, "HP-UX\n");
			break;

		case ELFOSABI_NETBSD:
			fprintf(stderr, "NetBSD\n");
			break;

		case ELFOSABI_LINUX:
			fprintf(stderr, "Linux\n");
			break;

		case ELFOSABI_SOLARIS:
			fprintf(stderr, "Sun Solaris\n");
			break;

		case ELFOSABI_AIX:
			fprintf(stderr, "IBM AIX\n");
			break;

		case ELFOSABI_IRIX:
			fprintf(stderr, "SGI Irix\n");
			break;

		case ELFOSABI_FREEBSD:
			fprintf(stderr, "FreeBSD\n");
			break;

		case ELFOSABI_TRU64:
			fprintf(stderr, "Compaq TRU64 UNIX\n");
			break;

		case ELFOSABI_MODESTO:
			fprintf(stderr, "Novell Modesto\n");
			break;

		case ELFOSABI_OPENBSD:
			fprintf(stderr, "OpenBSD\n");
			break;

		case ELFOSABI_ARM_AEABI:
			fprintf(stderr, "ARM EABI\n");
			break;

		case ELFOSABI_ARM:
			fprintf(stderr, "ARM\n");
			break;

		case ELFOSABI_STANDALONE:
			fprintf(stderr, "Standalone (embedded) app\n");
			break;

		default:
			fprintf(stderr, "Unknown (0x%x)\n", elf_header->e_ident[EI_OSABI]);
			break;
	}

	/* ELF filetype */
	fprintf(stderr, "Filetype \t= ");
	switch(elf_header->e_type)
	{
		case ET_NONE:
			fprintf(stderr, "N/A (0x0)\n");
			break;

		case ET_REL:
			fprintf(stderr, "Relocatable\n");
			break;

		case ET_EXEC:
			fprintf(stderr, "Executable\n");
			break;

		case ET_DYN:
			fprintf(stderr, "Shared Object\n");
			break;
		default:
			fprintf(stderr, "Unknown (0x%x)\n", elf_header->e_type);
			break;
	}

	/* ELF Machine-id */
	fprintf(stderr, "Machine\t\t= ");
	switch(elf_header->e_machine)
	{
		case EM_NONE:
			fprintf(stderr, "None (0x0)\n");
			break;

		case EM_386:
			fprintf(stderr, "INTEL x86 (0x%x)\n", EM_386);
			break;

		case EM_X86_64:
			fprintf(stderr, "AMD x86_64 (0x%x)\n", EM_X86_64);
			break;

		case EM_AARCH64:
			fprintf(stderr, "AARCH64 (0x%x)\n", EM_AARCH64);
			break;

		default:
			fprintf(stderr, " 0x%x\n", elf_header->e_machine);
			break;
	}

	/* Entry point */
	fprintf(stderr, "Entry point\t= 0x%08lx\n", elf_header->e_entry);

	/* ELF header size in bytes */
	fprintf(stderr, "ELF header size\t= 0x%08x\n", elf_header->e_ehsize);

	/* Program Header */
	fprintf(stderr, "Program Header\t= ");
	fprintf(stderr, "0x%08lx\n", elf_header->e_phoff);		/* start */
	fprintf(stderr, "\t\t  %d entries\n", elf_header->e_phnum);	/* num entry */
	fprintf(stderr, "\t\t  %d bytes\n", elf_header->e_phentsize);	/* size/entry */

	/* Section header starts at */
	fprintf(stderr, "Section Header\t= ");
	fprintf(stderr, "0x%08lx\n", elf_header->e_shoff);		/* start */
	fprintf(stderr, "\t\t  %d entries\n", elf_header->e_shnum);	/* num entry */
	fprintf(stderr, "\t\t  %d bytes\n", elf_header->e_shentsize);	/* size/entry */
	fprintf(stderr, "\t\t  0x%08x (string table offset)\n", elf_header->e_shstrndx);

	/* File flags (Machine specific)*/
	fprintf(stderr, "File flags \t= 0x%08x  ", elf_header->e_flags);

	/* ELF file flags are machine specific.
 * 	 * INTEL implements NO flags.
 * 	 	 * ARM implements a few.
 * 	 	 	 * Add support below to parse ELF file flags on ARM
 * 	 	 	 	 */
	int32_t ef = elf_header->e_flags;
	if(ef & EF_ARM_RELEXEC)
		fprintf(stderr, ",RELEXEC ");

	if(ef & EF_ARM_HASENTRY)
		fprintf(stderr, ",HASENTRY ");

	if(ef & EF_ARM_INTERWORK)
		fprintf(stderr, ",INTERWORK ");

	if(ef & EF_ARM_APCS_26)
		fprintf(stderr, ",APCS_26 ");

	if(ef & EF_ARM_APCS_FLOAT)
		fprintf(stderr, ",APCS_FLOAT ");

	if(ef & EF_ARM_PIC)
		fprintf(stderr, ",PIC ");

	if(ef & EF_ARM_ALIGN8)
		fprintf(stderr, ",ALIGN8 ");

	if(ef & EF_ARM_NEW_ABI)
		fprintf(stderr, ",NEW_ABI ");

	if(ef & EF_ARM_OLD_ABI)
		fprintf(stderr, ",OLD_ABI ");

	if(ef & EF_ARM_SOFT_FLOAT)
		fprintf(stderr, ",SOFT_FLOAT ");

	if(ef & EF_ARM_VFP_FLOAT)
		fprintf(stderr, ",VFP_FLOAT ");

	if(ef & EF_ARM_MAVERICK_FLOAT)
		fprintf(stderr, ",MAVERICK_FLOAT ");

	fprintf(stderr, "\n");

	/* MSB of flags conatins ARM EABI version */
	fprintf(stderr, "ARM EABI\t= Version %d\n", (ef & EF_ARM_EABIMASK)>>24);

	fprintf(stderr, "\n");	/* End of ELF header */

}

void
print_section_headers64(Elf64_Shdr sh_table[], int nsec, int strindx)
{
	uint32_t i;
	char* sh_str;	/* section-header string-table is also a section. */

	/* Compute section-header string-table address */
	sh_str = (char *) ( (char *)elf + sh_table[strindx].sh_offset );

	fprintf(stderr, "========================================");
	fprintf(stderr, "========================================\n");
	fprintf(stderr, "\t\tSection Headers\n");
	fprintf(stderr, " idx offset     load-addr          size       algn"
			" flags      type       section\n");

	for(i=0; i < nsec; i++) {
		fprintf(stderr, " %03d ", i);
		fprintf(stderr, "0x%08lx ", sh_table[i].sh_offset);
		fprintf(stderr, "0x%016lx ", sh_table[i].sh_addr);
		fprintf(stderr, "0x%08lx ", sh_table[i].sh_size);
		fprintf(stderr, "%4ld ", sh_table[i].sh_addralign);
		fprintf(stderr, "0x%08lx ", sh_table[i].sh_flags);
		fprintf(stderr, "0x%08x ", sh_table[i].sh_type);
		fprintf(stderr, "%s\t", (sh_str + sh_table[i].sh_name));
		fprintf(stderr, "\n");
	}
	fprintf(stderr, "\n");	/* end of section header table */
}

