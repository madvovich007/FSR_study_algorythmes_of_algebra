#include <iostream>

//смотрим тллько intelб видеокарты - RTX
class Programm{
private:
    char * name;
    int minRAM;
    int minGPU;
    int minCPU;
    int minHZ;
    int size;

    static int CPUseries;
    static int GPUmodel;
    static int RAM;
    static int SSD;
    static char screen;//i - ips, v - VA, O - OLED
    static int width;
    static int hight;
    static int HZ;

    static char * copystr(char * str);
public:
    Programm(char * name, int ram, int cpu, int gpu, int hz, int  size = 0);
    Programm();
    ~Programm();

    void set_name(char * newname);
    void set_minRAM(int ram);
    void set_minCPU(int cpu);
    void set_minGPU(int gpu);
    void set_minHZ(int hz);
    int set_size(int  size);

    static int set_CPUseries(int series);
    static int set_GPUmodel(int model);
    static int set_RAM(int gb);
    static int set_SSD(int gb);
    static int set_Screen(char type);
    static int set_Resolution(int w, int h);
    static int set_HZ(int hz);

    char * get_name();
    int get_minRAM();
    int get_minCPU();
    int get_minGPU();
    int get_minHZ();
    int get_size();

    static int get_CPUseries();
    static int get_GPUmodel();
    static int get_RAM();
    static int get_SSD();
    static char get_screen();
    static int get_width();
    static int get_hight();
    static int get_HZ();

    int canRun();
};


char * Programm::copystr(char * s){
    if (s == nullptr){
        return nullptr;
    }
    int len = 0;
    while (s[len] != '\0'){
        len++;
    }
    char * res = new char[len + 1];
    for (int i = 0; i <= len; i++){
        res[i] = s[i];
    }
    return res;
}

int Programm::CPUseries = 0;
int Programm::GPUmodel = 0;
int Programm::RAM = 0;
int Programm::SSD = 0;
char Programm::screen = 'i';
int Programm::width = 0;
int Programm::hight = 0;
int Programm::HZ = 0;


Programm::Programm() : name(nullptr), minRAM(0), minCPU(0), minGPU(0), minHZ(0), size(0){}

Programm::Programm(char * programName, int ram, int cpu, int gpu, int hz, int  size): name(copystr(programName)), minRAM(ram), minCPU(cpu), minGPU(gpu), minHZ(hz),  size(0){
    if ( size > 0 && !set_size(size)){
        std::cout << "Недостаточно места на диске для " << get_name();
    }
}

void Programm::set_name(char * newName){
    char * copy = copystr(newName);
    delete[] name;
    name = copy;
}

void Programm::set_minRAM(int ram){
    minRAM = ram;
}
void Programm::set_minCPU(int cpu) {
    minCPU = cpu;
}
void Programm::set_minGPU(int gpu) {
    minGPU = gpu;
}
void Programm::set_minHZ(int hz) {
    minHZ = hz;
}

int Programm::set_size(int newsize){
    if (newsize < 0 || newsize - size > SSD) {
        return 0;
    }
    SSD += size - newsize;
    size = newsize;
    return 1;
}

int Programm::set_CPUseries(int series){
    if (series != 3 && series != 5 && series != 7 && series != 9){
        return 0;
    }
    CPUseries = series;
    return 1;
}

int Programm::set_GPUmodel(int model){
    if (model != 0 && model < 2000){
        return 0;
    }
    GPUmodel = model;
    return 1;
}


int Programm::set_RAM(int gb){
    if (gb <= 0){
        return 0;
    }
    RAM = gb;
    return 1;
}

int Programm::set_SSD(int gb){
    if (gb < 0){
        return 0;
    }
    SSD = gb;
    return 1;
}


int Programm::set_Screen(char type){
    switch (type){
        case 'i':
            screen = 'i';
            return 1;
        case 'I':
            screen = 'i';
            return 1;
        case 'v':
            screen = 'v';
            return 1;
        case 'V':
            screen = 'v';
            return 1;
        case 'o':
            screen = 'O';
            return 1;
        case 'O':
            screen = 'O';
            return 1;
        default:
            return 0;
    }
}


int Programm::set_Resolution(int w, int h){
    if (w <= 0 || h <= 0){
        return 0;
    }
    width = w;
    hight = h;
    return 1;
}


int Programm::set_HZ(int hz){
    if (hz <= 0){
        return 0;
    }
    HZ = hz;
    return 1;
}

Programm::~Programm(){
    SSD +=  size;
    delete[] name;
    name = nullptr;
     size = 0;
}

char * Programm::get_name() {
    if (name == nullptr) {
        return nullptr;
    }
    return name;
}
int Programm::get_minRAM() {
    return minRAM;
}
int Programm::get_minCPU() {
    return minCPU;
}
int Programm::get_minGPU() {
    return minGPU;
}
int Programm::get_minHZ() {
    return minHZ;
}
int Programm::get_size() {
    return  size;
}

int Programm::canRun() {
    if (RAM >= minRAM && CPUseries >= minCPU && GPUmodel >= minGPU && HZ >= minHZ) {
        return 1;
    }
    return 0;
}

int Programm::get_CPUseries() {
    return CPUseries;
}

int Programm::get_GPUmodel() {
    return GPUmodel;
}

int Programm::get_RAM() {
    return RAM;
}

int Programm::get_SSD() {
    return SSD;
}

char Programm::get_screen() {
    return screen;
}

int Programm::get_width() {
    return width;
}

int Programm::get_hight() {
    return hight;
}

int Programm::get_HZ() {
    return HZ;
}

int main(){
    Programm::set_CPUseries(5);
    Programm::set_GPUmodel(3070);
    Programm::set_RAM(32);
    Programm::set_SSD(1000);
    Programm::set_Screen('o');
    Programm::set_Resolution(2560, 1440);
    Programm::set_HZ(240);
    std::cout << "Свободно на SSD: " << Programm::get_SSD() << "ГБ\n";

    Programm aimp("AIMP", 1, 3, 0, 0, 1);
    Programm music("Яндекс Музыка", 2, 3, 0, 0, 2);
    Programm cs("Counter-Strike 2", 8, 5, 2060, 60, 40);
    Programm GTA6("GTA 6", 32, 9, 5090, 120, 200);
    Programm word("Microsoft Word", 4, 3, 0, 60, 5);
    Programm excel("Microsoft Excel", 4, 3, 0, 60, 4);
    Programm pycharm("PyCharm", 8, 5, 0, 60, 15);
    Programm clion("CLion", 8, 5, 0, 60, 12);
    Programm chrome("Google Chrome", 4, 5, 0, 60, 3);
    std::cout << "Свободно на SSD: " << Programm::get_SSD() << "ГБ\n";
    std::cout << "ГТА запустится:" << GTA6.canRun() << "\n";
    
    return 0;
}
