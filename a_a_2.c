#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// サブスレッドで実行する関数
void* square_calculator(void* arg) {
    // 1. 引数を受け取る（void* から int* へキャスト）
    int* input_ptr = (int*)arg;
    int value = *input_ptr;

    printf("  [Sub] %d の2乗を計算中...\n", value);
    sleep(2); // 計算に時間がかかるフリ

    // 2. 結果を保存するためのメモリを確保する
    // ※関数のローカル変数を返すとスレッド終了時に消えてしまうため、mallocを使います
    int* result = malloc(sizeof(int));
    *result = value * value;

    printf("  [Sub] 計算完了！\n");

    // 3. 結果の「住所（ポインタ）」を返す（Futureの完了に相当）
    return (void*)result;
}

int main() {
    pthread_t thread;
    int number;

    printf("[Main] 2乗したい数字を入力してください: ");
    scanf("%d", &number);

    // 1. スレッドを生成し、numberの「住所」を渡す
    /* TODO: pthread_create を使って、square_calculator に &number を渡して起動 */
    pthread_create(&thread, NULL, square_calculator, (void*)&number);

    printf("[Main] 計算中に別の作業（ドット表示）をします...\n");
    
    // スレッドが動いている間、メインは待たずに進む
    for(int i = 0; i < 4; i++) {
        printf(".\n");
        usleep(500000);
    }

    // 2. スレッドの終了を待ち、結果を受け取る
    void* return_value; // ここに結果の住所が届く
    /* TODO: pthread_join を使い、第2引数に &return_value を渡して合流を待つ */
    pthread_join(thread, &return_value);

    // 3. 受け取った結果（void*）を int* に戻して表示
    int* final_result = (int*)return_value;
    printf("[Main] 計算結果を受け取りました: %d\n", *final_result);

    // mallocしたメモリを解放
    free(final_result);
    printf("[Main] 終了します。\n");

    return 0;
}