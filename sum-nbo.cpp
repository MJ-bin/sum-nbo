#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    uint32_t sum = 0;
	uint32_t network_byte_order;
	
	if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> [file2 ...]\n", argv[0]);
        return 1;
    }
    
	// argv[0]은 프로그램 이름이므로 argv[1]부터 시작
    for (int i = 1; i < argc; i++) {
        FILE* fp = fopen(argv[i], "rb");

		// 파일 핸들 반환 실패
		if (fp == NULL) {
		    perror(argv[i]);
		    return 1;
		}

		// 파일 읽기 실패
		if (fread(&network_byte_order,
		          sizeof(network_byte_order),
		          1,
		          fp) != 1) {
		    		fprintf(stderr, "%s: failed to read 4 bytes\n", argv[i]);
		    		fclose(fp);
		    		return 1;
		}

        fclose(fp);

        // Network Byte Order → Host Byte Order(little-endian)
        uint32_t host_value = ntohl(network_byte_order);
        sum += host_value;

        if (i > 1) printf(" + ");

        printf("%d(0x%08x)", host_value, host_value);
    }

    printf(" = %d(0x%08x)\n", sum, sum);
    return 0;
}
