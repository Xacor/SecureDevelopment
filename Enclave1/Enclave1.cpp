#include "sgx_trts.h"
#include "Enclave1_t.h"
#include <string.h>
const char table[5][6] = {
	"Text1",
	"Text2",
	"Text3",
	"Text4",
	"Text5"
};

void get(char* buf, size_t len, size_t idx) {
	if (idx < 5) {
		const char* data_ptr = table[idx];
		memcpy(buf, data_ptr, strlen(data_ptr));
	}
	else {
		memset(buf, 0, strlen(table[0]));
	}
	return;
}