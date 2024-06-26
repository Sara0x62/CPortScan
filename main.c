// Imports
#include <limits.h>
#include <netinet/in.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

// Top 1000 TCP ports
#define PORT_COUNT 1000
const uint16_t PORTS[] = {80, 23, 443, 21, 22, 25, 3389, 110, 445, 139, 143, 53, 135, 3306, 8080, 1723, 111, 995, 993, 5900, 1025, 587, 8888, 199, 1720, 465, 548, 113, 81, 6001, 10000, 514, 5060, 179, 1026, 2000, 8443, 8000, 32768, 554, 26, 1433, 49152, 2001, 515, 8008, 49154, 1027, 5666, 646, 5000, 5631, 631, 49153, 8081, 2049, 88, 79, 5800, 106, 2121, 1110, 49155, 6000, 513, 990, 5357, 427, 49156, 543, 544, 5101, 144, 7, 389, 8009, 3128, 444, 9999, 5009, 7070, 5190, 3000, 5432, 1900, 3986, 13, 1029, 9, 5051, 6646, 49157, 1028, 873, 1755, 2717, 4899, 9100, 119, 37, 1000, 3001, 5001, 82, 10010, 1030, 9090, 2107, 1024, 2103, 6004, 1801, 5050, 19, 8031, 1041, 255, 1049, 1048, 2967, 1053, 3703, 1056, 1065, 1064, 1054, 17, 808, 3689, 1031, 1044, 1071, 5901, 100, 9102, 8010, 2869, 1039, 5120, 4001, 9000, 2105, 636, 1038, 2601, 1, 7000, 1066, 1069, 625, 311, 280, 254, 4000, 1993, 1761, 5003, 2002, 2005, 1998, 1032, 1050, 6112, 3690, 1521, 2161, 6002, 1080, 2401, 4045, 902, 7937, 787, 1058, 2383, 32771, 1033, 1040, 1059, 50000, 5555, 10001, 1494, 593, 2301, 3, 1, 3268, 7938, 1234, 1022, 1074, 8002, 1036, 1035, 9001, 1037, 464, 497, 1935, 6666, 2003, 6543, 1352, 24, 3269, 1111, 407, 500, 20, 2006, 3260, 15000, 1218, 1034, 4444, 264, 2004, 33, 1042, 42510, 999, 3052, 1023, 1068, 222, 7100, 888, 4827, 1999, 563, 1717, 2008, 992, 32770, 32772, 7001, 8082, 2007, 740, 5550, 2009, 5801, 1043, 512, 2701, 7019, 50001, 1700, 4662, 2065, 2010, 42, 9535, 2602, 3333, 161, 5100, 5002, 2604, 4002, 6059, 1047, 8192, 8193, 2702, 6789, 9595, 1051, 9594, 9593, 16993, 16992, 5226, 5225, 32769, 3283, 1052, 8194, 1055, 1062, 9415, 8701, 8652, 8651, 8089, 65389, 65000, 64680, 64623, 55600, 55555, 52869, 35500, 33354, 23502, 20828, 1311, 1060, 4443, 730, 731, 709, 1067, 13782, 5902, 366, 9050, 1002, 85, 5500, 5431, 1864, 1863, 8085, 51103, 49999, 45100, 10243, 49, 3495, 6667, 90, 475, 27000, 1503, 6881, 1500, 8021, 340, 78, 5566, 8088, 2222, 9071, 8899, 6005, 9876, 1501, 5102, 32774, 32773, 9101, 5679, 163, 648, 146, 1666, 901, 83, 9207, 8001, 8083, 5004, 3476, 8084, 5214, 14238, 12345, 912, 30, 2605, 2030, 6, 541, 8007, 3005, 4, 1248, 2500, 880, 306, 4242, 1097, 9009, 2525, 1086, 1088, 8291, 52822, 6101, 900, 7200, 2809, 395, 800, 32775, 12000, 1083, 211, 987, 705, 20005, 711, 13783, 6969, 3071, 5269, 5222, 1085, 1046, 5987, 5989, 5988, 2190, 11967, 8600, 3766, 7627, 8087, 30000, 9010, 7741, 14000, 3367, 1099, 1098, 3031, 2718, 6580, 15002, 4129, 6901, 3827, 3580, 2144, 9900, 8181, 3801, 1718, 2811, 9080, 2135, 1045, 2399, 3017, 10002, 1148, 9002, 8873, 2875, 9011, 5718, 8086, 3998, 2607, 11110, 4126, 5911, 5910, 9618, 2381, 1096, 3300, 3351, 1073, 8333, 3784, 5633, 15660, 6123, 3211, 1078, 3659, 3551, 2260, 2160, 2100, 16001, 3325, 3323, 1104, 9968, 9503, 9502, 9485, 9290, 9220, 8994, 8649, 8222, 7911, 7625, 7106, 65129, 63331, 6156, 6129, 60020, 5962, 5961, 5960, 5959, 5925, 5877, 5825, 5810, 58080, 57294, 50800, 50006, 50003, 49160, 49159, 49158, 48080, 40193, 34573, 34572, 34571, 3404, 33899, 3301, 32782, 32781, 31038, 30718, 28201, 27715, 25734, 24800, 22939, 21571, 20221, 20031, 19842, 19801, 19101, 17988, 1783, 16018, 16016, 15003, 14442, 13456, 10629, 10628, 10626, 10621, 10617, 10616, 10566, 10025, 10024, 10012, 1169, 5030, 5414, 1057, 6788, 1947, 1094, 1075, 1108, 4003, 1081, 1093, 4449, 1687, 1840, 1100, 1063, 1061, 1107, 1106, 9500, 20222, 7778, 1077, 1310, 2119, 2492, 1070, 20000, 8400, 1272, 6389, 7777, 1072, 1079, 1082, 8402, 89, 691, 1001, 32776, 1999, 212, 2020, 6003, 7002, 2998, 50002, 3372, 898, 5510, 32, 2033, 4165, 3061, 5903, 99, 749, 425, 43, 5405, 6106, 13722, 6502, 7007, 458, 9666, 8100, 3737, 5298, 1152, 8090, 2191, 3011, 1580, 5200, 3851, 3371, 3370, 3369, 7402, 5054, 3918, 3077, 7443, 3493, 3828, 1186, 2179, 1183, 19315, 19283, 3995, 5963, 1124, 8500, 1089, 10004, 2251, 1087, 5280, 3871, 3030, 62078, 9091, 4111, 1334, 3261, 2522, 5859, 1247, 9944, 9943, 9877, 9110, 8654, 8254, 8180, 8011, 7512, 7435, 7103, 61900, 61532, 5922, 5915, 5904, 5822, 56738, 55055, 51493, 50636, 50389, 49175, 49165, 49163, 3546, 32784, 27355, 27353, 27352, 24444, 19780, 18988, 16012, 15742, 10778, 4006, 2126, 4446, 3880, 1782, 1296, 9998, 9040, 32779, 1021, 32777, 2021, 32778, 616, 666, 700, 5802, 4321, 545, 1524, 1112, 49400, 84, 38292, 2040, 32780, 3006, 2111, 1084, 1600, 2048, 2638, 6699, 9111, 16080, 6547, 6007, 1533, 5560, 2106, 1443, 667, 720, 2034, 555, 801, 6025, 3221, 3826, 9200, 2608, 4279, 7025, 11111, 3527, 1151, 8200, 8300, 6689, 9878, 10009, 8800, 5730, 2394, 2393, 2725, 5061, 6566, 9081, 5678, 3800, 4550, 5080, 1201, 3168, 3814, 1862, 1114, 6510, 3905, 8383, 3914, 3971, 3809, 5033, 7676, 3517, 4900, 3869, 9418, 2909, 3878, 8042, 1091, 1090, 3920, 6567, 1138, 3945, 1175, 10003, 3390, 3889, 1131, 8292, 5087, 1119, 1117, 4848, 7800, 16000, 3324, 3322, 5221, 4445, 9917, 9575, 9099, 9003, 8290, 8099, 8093, 8045, 7921, 7920, 7496, 6839, 6792, 6779, 6692, 6565, 60443, 5952, 5950, 5907, 5906, 5862, 5850, 5815, 5811, 57797, 56737, 5544, 55056, 5440, 54328, 54045, 52848, 52673, 50500, 50300, 49176, 49167, 49161, 44501, 44176, 41511, 40911, 32785, 32783, 30951, 27356, 26214, 25735, 19350, 18101, 18040, 17877, 16113, 15004, 14441, 12265, 12174, 10215, 10180, 4567, 6100, 4004, 4005, 8022, 9898, 7999, 1271, 1199, 3003, 1122, 2323, 4224, 2022, 617, 777, 417, 714, 6346, 981, 722, 1009, 4998, 70, 1076, 5999, 10082, 765, 301, 524, 668, 2041, 6009, 1417, 1434, 259, 44443, 1984, 2068, 7004, 1007, 4343, 416, 2038, 6006, 109, 4125, 1461, 9103, 911, 726, 1010, 2046, 2035, 7201, 687, 2013, 481, 125, 6669, 6668, 903, 1455, 683, 1011, 2043, 2047, 31337, 256, 9929, 5998, 406, 44442, 783, 843, 2042, 2045, 4040, 6060, 6051, 1145, 3916, 9443, 9444, 1875, 7272, 4252, 4200, 7024, 1556, 13724, 1141, 1233, 8765, 1137, 3963, 5938, 9191, 3808, 8686, 3981, 2710, 3852, 3849, 3944, 3853, 9988, 1163, 4164, 3820, 6481, 3731, 5081, 40000, 8097, 4555, 3863, 1287, 4430, 7744, 1812, 7913, 1166, 1164, 1165, 8019, 10160, 4658, 7878, 3304, 3307, 1259, 1092};

// Functions
void* worker(void*);
void port_scan(char*, uint16_t, struct addrinfo*);
void print_usage();

typedef struct {
    unsigned int thread_id;
    char* target_ip;
    struct addrinfo* addrs;
    unsigned int ports_thread;
    uint16_t* port_range;
} thread_args;

int main(int argc, char* argv[])
{
    // ./pscan URL THREADS
    //    [0]  [1]  [2]
    if (argc <= 1) { print_usage(); exit(0);}

    unsigned int THREAD_COUNT = 20;

    // If custom thread count was given in startup args:
    if (argc == 3) {
        unsigned long tmp = strtoul(argv[2], NULL, 0);
        if (tmp < 0 || tmp > UINT_MAX) {
            printf("Invalid thread count\n");
            exit(1);
        }
        THREAD_COUNT = tmp;
        printf("SET - Custom thread count of : %d\n", THREAD_COUNT);
    }

    // Set up threads array
    pthread_t threads[THREAD_COUNT];

    // String length of our target, needed for a later malloc call
    unsigned int target_len = strlen(argv[1]);

    // Calculate how many ports each thread gets assigned
    int ports_per_thread = PORT_COUNT / THREAD_COUNT;

    // get the addresses of target
    struct addrinfo *results;
    struct addrinfo hints;

    // Configure our addr structs
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    int res = getaddrinfo(argv[1], "80", &hints, &results);
    if (res != 0) { printf("Error occured getting addrinfo\n"); exit(1); }

    // Get the actual IP address for our target - we're only grabbing the 'first' result here
    // As some domains have multiple assigned IPs
    struct sockaddr_in* ipv4 = (struct sockaddr_in*) results->ai_addr;
    char* ip = malloc(INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &(ipv4->sin_addr), ip, INET_ADDRSTRLEN);
    printf("Got target IP: %s\n", ip);


    // Start setting up our threads;
    printf("[*] - Setting up %d threads...\n", THREAD_COUNT);
    int start = 0;
    for (int x = 0; x < THREAD_COUNT; x++) {

        // Setting new struct with thread_id
        // printf("[*] - Allocating struct args...\n");
        thread_args* args = malloc(sizeof(thread_args));
        args->thread_id = x;
        args->ports_thread = ports_per_thread;

        // Target ip
        // printf("[*] - Allocating target ip...\n");
        args->target_ip = malloc( target_len + 1);
        strcpy(args->target_ip, ip);

        // Addrinfo results;
        args->addrs = results;

        // Ports per thread...
        args->port_range = malloc(sizeof(uint16_t) * ports_per_thread);
        memset(args->port_range, '\0', sizeof(uint16_t) * ports_per_thread);

        // Spliting ports for every thread
        for (int z = 0; z < ports_per_thread; z++) {
            // printf("[*] - Z = %d | Start = %d\n", z, start);
            args->port_range[z] = PORTS[start];
            start++;
        }
 
        // Make the thread, it starts running at this point;
        pthread_create( &threads[x], NULL, worker, args);
    }

    printf("[*] - Joining threads and waiting till scan is done...\n");
    for (int x = 0; x < THREAD_COUNT; x++)
    {
        // Join them together and wait till done...
        pthread_join(threads[x], NULL);
    }

    printf("[*] - done\n");
    return 0;
}

void port_scan(char* ip, uint16_t port, struct addrinfo* addrs)
{
    // Initialize socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) { printf("Error occured during opening of socket..."); exit(1);}

    // Setup our sockaddr for our remote target
    struct sockaddr_in remote = {};
    remote.sin_port = htons(port);  // htons to convert between endianness
    remote.sin_family = AF_INET;
    if ( inet_pton(AF_INET, ip, &remote.sin_addr) <= 0) { printf("\nError occured setting IP \n"); }    // Converts the IP into a binary network format
    memset(remote.sin_zero, '\0', sizeof(remote.sin_zero));

    // Attempt connection
    int res = connect(sock, (struct sockaddr*) &remote, sizeof(remote));

    // if res == 0, successfull otherwise the port is likely closed or another error occurred
    if (res == 0) {
        printf("PORT: %6d | OPEN\n", port);
    } else {
        // An error outside of the simple connection refused (closed port) occurred
        if (res != ECONNREFUSED) {
            printf("PORT: %6d | ERROR: %m\n", port, errno);
        }
        fflush(stdout);
    }

    // Cleaning
    shutdown(sock, SHUT_RDWR);
    close(sock);
}

void *worker(void *args)
{
    // Get our arguments for this specific thread
    thread_args f_args = * ((thread_args*) args);

    // Start scanning our assigned ports
    for (int x = 0; x < f_args.ports_thread; x++) {
        port_scan(f_args.target_ip, f_args.port_range[x], f_args.addrs);
    }
}

void print_usage() {
    printf("Usage: ./pscan TARGET *THREADS\n");
    printf("- Target: A url or ip you wish to scan e.g. 'www.google.com'\n");
    printf("- *THREADS: Optional, if you wish to set a custom thread count, DEFAULT = 20\n");
    printf("- Example usage:\n './pscan www.google.com'\nor\n './pscan www.google.com 50\n");
}
