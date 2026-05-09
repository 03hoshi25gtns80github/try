#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// 「重い処理」を想定した関数
void* heavy_task(void* arg) {
    printf("  [Task] 重い処理を開始します...\n");
    sleep(3); // 3秒待機（ネットワーク通信やDBアクセスの代わり）
    printf("  [Task] 重い処理が完了しました！\n");
    return NULL;
}

int main() {
    pthread_t thread_id;

    printf("[Main] スレッドを生成します。\n");
    
    // スレッドを生成して、heavy_taskを非同期に開始
    pthread_create(&thread_id, NULL, heavy_task, NULL);

    printf("[Main] 別の作業（UI更新など）を続けます...\n");
    for(int i = 0; i < 5; i++) {
        printf("[Main] 作業中... %d\n", i);
        usleep(1000000); // 0.5秒ずつ表示
    }

    // 最後にスレッドの終了を待つ（これが無いと完了前にメインが終わる）
    pthread_join(thread_id, NULL);
    printf("[Main] 全ての処理が終了しました。\n");

    return 0;
}