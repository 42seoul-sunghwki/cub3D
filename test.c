#include <stdio.h>
#include <stdlib.h>
#include "bass.h"
#include <unistd.h>

int main() {
    // BASS 라이브러리 초기화
    if (!BASS_Init(-1, 44100, 0, 0, NULL)) {
        printf("BASS 초기화 실패: %s\n", BASS_ErrorGetCode());
        return -1;
    }
    // 음악 파일 로드
    HSTREAM streamHandle = BASS_StreamCreateFile(FALSE, "src/bonus/original.mp3", 0, 0, 0);
    if (!streamHandle) {
        printf("파일 로드 실패: %s\n", BASS_ErrorGetCode());
        BASS_Free();
        return -1;
    }
    // 음악 재생
    BASS_ChannelPlay(streamHandle, FALSE);
    printf("재생 중... 'test.mp3'\n");
    // 음악이 끝날 때까지 대기
    while (BASS_ChannelIsActive(streamHandle) == BASS_ACTIVE_PLAYING) {
        // 이 부분에 적절한 sleep 함수를 사용해 CPU 사용률을 관리할 수 있습니다.
        sleep(100);
    }
    // 라이브러리 해제
    BASS_StreamFree(streamHandle);
    BASS_Free();
    return 0;
}