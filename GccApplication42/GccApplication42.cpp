#include <avr/io.h>

void EEPROM_write_string(int address, int lenght, int *data)
{
	while (lenght)
	{
		while (EECR & (1 << 1));
		EEAR = address;
		address = address + 1;
		EEDR = *data;
		data = data + 1;
		EECR |= (1 << 2);
		EECR |= (1 << 1);
		lenght = lenght - 1;
	}
}

void EEPROM_read_string(int address, int lenght, int *data)
{
	while (EECR & (1 << 1));
	while (lenght--)
	{
		EEAR = address++;
		EECR |= (1 << 0);
		*data = EEDR;
		data++;
	}
}

int main(void)
{
	static char stroka_iz_ram_v_eeprom[5] ="1";
	EEPROM_write_string(0x00, 5, &stroka_iz_ram_v_eeprom[0]);
	static char stroka_iz_eeprom_v_ram[5];
	EEPROM_read_string(0x00, 5, &stroka_iz_eeprom_v_ram[0]);

}