#include <stdio.h>
#include <stdint.h>
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
		    perror(argv[i]);	// 어떤 파일에서 open 이 실패했는지 명시
		    return 1;
		}

		// 파일 읽기 실패
		// 코드는 이렇게 짜라 - gilgil 멘토님
		// fread 는 파일로부터 데이터를 읽을때, 아이템 크기보다 작은 자투리 데이터는 읽지 못하고 버린다.
		if (fread(&network_byte_order,					// 읽은 데이터를 저장할 버퍼 주소
		          1,									// 읽을 아이템의 크기
		          sizeof(network_byte_order),			// 읽을 아이템의 개수, sizeof 는 함수호출이 아니라 컴파일 전의 전처리 과정에서 해제됨.
		          fp) != sizeof(network_byte_order)) {	// fread 의 반환값은 읽은 아이템의 개수이다.
		/*
		if (fread(&network_byte_order,
		          sizeof(network_byte_order),
		          1,
		          fp) != 1) {
		*/
		// fread 를 사용할때, 1바이트 아이템을 4번 읽는 것이 관리에 좋다.
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
    return 0;	// main func 는 int 함수라도 return 0 명시가 필요없다. 알아서 넣어줌
}
