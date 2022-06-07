## 사용법

> bopen과 bclose는 FILE 과 사용법이 같음으로 생략

### void bread(TYPE type, BITFILE *bf, void * data, int bitSize, int length);
>  파일에서 데이터를 bitSize만큼 length번 읽어서 data 변수에 대입.
>  
>  이때, data의 타입은 type변수에 적어준다. (INT, CHAR)

### void bwrite(TYPE type, BITFILE *bf, void * data, int bitSize, int length);
> data에서 bitSize만큼 length번 읽어서 파일에 출력.
> 
> 이때, data의 타입은 type변수에 적어준다. (INT, CHAR)

### void bflush(BITFILE *bf);
> write모드 일때만 사용
> 
> buffer내의 잔여 비트를 모두 파일에 출력할 수 있도록 fclose 직전에 한번 호출해줘야됨.


### 읽기

```c
#include "bit.h"

int main(){

    BITFILE * bf; //비트파일 포인터 선언
    bf = bopen("data.bin", "rb"); //data.bin파일을 읽기모드로 열기

    int data;

    //해당 파일에서 3비트만큼 1번 읽어와 data파일에 할당해줌
    bread(INT, bf, &data, 3, 1);

    bclose(bf); //BITFILE 해제

    return 0;
}

```

### 쓰기

```c
#include "bit.h"

int main(){

    BITFILE * bf; //비트파일 포인터 선언
    bf = bopen("data.bin", "wb"); //data.bin파일을 읽기모드로 열기

    int data = 4;

    //data 변수에서 3비트를 1번 반복하여 data.bin파일에 저장
    bwrite(INT, bf, &data, 3, 1);

    bflush(bf);//write 모드에서는 bclose이전에 꼭 해줘야함
    bclose(bf); //BITFILE 해제

    return 0;
}
```
