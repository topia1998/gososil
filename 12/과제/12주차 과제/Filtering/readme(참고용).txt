12주차 과제 조교용 입니다.

고소실 2주차 실습 코드를 기반으로 만들었습니다.

실행시 윈도우 도구창 b1, b2를 클릭하면 Gaussian filtering을 하도록 만들었습니다.
B1은 shared memory를 사용하지 않는 커널, B2는 shared memory를 사용하는 커널입니다.

Shared memory 크기는 thread block 크기보다 가로 세로 모두 window 크게 잡았습니다.
윈도우 사이즈는 2로 고정했습니다. 학생들은 cuda_code.cu에 있는 2개의 커널과
커널을 시작하기까지의 과정, 메모리 복사하는 과정까지를 작성하여 제출하도록 했습니다.