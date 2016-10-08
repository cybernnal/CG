#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int	main(void)
{
	wchar_t ac = L'¯';
	
	setlocale(LC_CTYPE,"fr_FR.UTF-8");

	wprintf(L"%C\n", 8254);
	return 0;
}
