#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define SERIAL_PORT "/dev/ttyACM0"
#define BAUDRATE   B9600

int main() {
    int uart = open(SERIAL_PORT, O_RDWR | O_NOCTTY);
    if (uart < 0) {
        perror("Port not opened");
        return -1;
    }

    struct termios options;

    memset(&options, 0, sizeof(options));

    tcgetattr(uart, &options);    // dosya tanimlayticisina (uart) bagli terminalin mevcut ayarlarini alir ve kullaniciya ait termios yapisina doldurur. 

    cfsetispeed(&options, BAUDRATE);
    cfsetospeed(&options, BAUDRATE);

    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8; // 8 bit veri uzunlugu
    options.c_iflag &= ~IGNBRK; // break sinyalini (uzun sureli LOW kalma durumudur) break sinyalini ignore etme isi kapali yani algilayacak
    options.c_lflag = 0; // noncanonical mode
    options.c_oflag = 0; // ham veri gonderilecek

    options.c_cc[VMIN] = 1; // en az 1 karakter okuyacak (em az 1 byte alacak)
    options.c_cc[VTIME] = 1;// 0.1 sn timeout (veri gelmezse 100 ms sonra cik)

    options.c_iflag &= ~(IXANY | IXON | IXOFF); // software flow control closed.
        // sebebi ise eger acik olursa XOFF(0x13) gibi karakterler verinin icinde normal bir byte olabilir.
    options.c_cflag |= (CLOCAL | CREAD); // read mod active , and , 
        // CLOCAL ile modem sinyallerini bosver sadece veriyle ilgilen diyoruz. modem sinyali iki taraf arasinda hazir olma durumunu kontrol eder
        // MCU' lar bu sinyalleri genelde kullanmazlar. UART iletisimi genelde 3 hat uzreinden olur RX , TX , GND  
        // bu sinyaller kullanilmadigi icin varligi sinyali kilitleyebilir.        
    options.c_cflag &= ~(PARENB | PARODD); // parity bit disable
    options.c_cflag &= ~CSTOPB; // 1 tane stop biti kullan demektir. eger CTOPB=0 ise 1 bit , CSTOPB=1 ise 2 stop biti kullanilir.
        // receiver'a veri bitti sinyali verir ve bir sonraki karakter icin hazirlanmasina zaman tanir
    options.c_cflag &= ~CRTSCTS; // hardware flow control disable RTS: request to send , CTS: clear to send
        // transmitter --> RTS LOW yapar 'i want to send data' ,, receiver  --> CTS LOW yapar "ready, you can send"
        // UART icin gerekli degildir otomatik olur. USB-TTL CTS pini bagli degilse bu CRTSCTS aktiflestirilirse UART veri gonderemez. 
        // CTS pininin LOW olmasini bekler. bagli olmadigi icin hic LOW olmaz. 

    tcsetattr(uart, TCSANOW, &options);
        
    printf(">> Serial terminal started. TO close Ctrl+C\n");

    char input[16];

    while (1) {
        memset(input, 0, sizeof(input));
        
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        tcflush(uart, TCIOFLUSH);
        
        if (strlen(input) > 0) {
            write(uart, input, strlen(input)); 
        }
    } 
    close(uart);
    return 0;
}