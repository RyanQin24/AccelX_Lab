#include "TimeSeries.h"

TimeSeries::TimeSeries(){
    array_size = min_array_size;
    speed_array = new speed_data[min_array_size];
    acceleration_array = new acceleration_data[min_array_size];
}

TimeSeries::~TimeSeries(){
    delete[] speed_array;
    delete[] acceleration_array;
    array_size = 0;
    array_used_capacity = 0;
}

void TimeSeries::LoadCSV(std::string filename){
    delete[] speed_array;
    delete[] acceleration_array;
    array_size = min_array_size;
    array_used_capacity = 0;
    IntegrateFlag = false;
    speed_array = new speed_data[min_array_size];
    acceleration_array = new acceleration_data[min_array_size];
    CalcErr();
    std::ifstream csvfile(filename);
    std::string csvStringElement;
    std::string x;
    std::string y;
    std::string z;
    while(std::getline(csvfile,csvStringElement)){
        std::stringstream ss(csvStringElement);
        std::getline(ss,x,',');
        std::getline(ss,y,',');
        std::getline(ss,z);
        if(array_used_capacity >= array_size){
            doubleArray();
        }
        acceleration_array[array_used_capacity].x = std::stoi(x);
        acceleration_array[array_used_capacity].y = std::stoi(y);
        acceleration_array[array_used_capacity].z = std::stoi(z);
        array_used_capacity++;
    }
    std::cout <<"************ " <<std::endl;
    std::cout << "Loaded acceleration data!" << std::endl;
    for(std::size_t i{0}; i < array_used_capacity; i++){
        acceleration_array[i].ax = (double)acceleration_array[i].x * scalar - offset_x - g;
        acceleration_array[i].ay = (double)acceleration_array[i].y * scalar - offset_y;
        acceleration_array[i].az = (double)acceleration_array[i].z * scalar - offset_z;
    }
    std::cout <<"************ " <<std::endl;
    std::cout << "Scalar and Offset Calculated!" << std::endl;
    std::cout << "Success" << std::endl;
}

void TimeSeries::PrintData(){
    if(array_used_capacity == 0 || !IntegrateFlag){
        std::cout <<"Failure" <<std::endl;
    }else{
        std::cout <<"Printing Speed data..." <<std::endl;
        for(std::size_t i{0}; i < array_used_capacity; i++){
            std::cout << "Time: " << i*time_interval << " s, ";
            std::cout << "Speed: " << speed_array[i].magnitude << " m/s"<< std::endl;
            std::cout << std::endl;
        }
    }
}

void TimeSeries::Integrate(std::string algorithm){
    if(array_used_capacity <= 1 || !(algorithm == "trapzoid" || algorithm == "back4pt")){
        std::cout << "Failure" << std::endl;
        return;
    }
    double tempx{0.0};
    double tempy{0.0};
    double tempz{0.0};
    for(std::size_t i{1}; i < array_used_capacity; i++){
        if(algorithm == "trapzoid"){
            Trapezoidal(i, tempx, tempy, tempz);
        }else if (algorithm == "back4pt"){
            Back4Pt(i, tempx, tempy, tempz);
        }
        speed_array[i].x = tempx;
        speed_array[i].y = tempy;
        speed_array[i].z = tempz;
        speed_array[i].magnitude = VectorMagnitude(i);
    }
    IntegrateFlag = true;
    std::cout << "Integration Success!" << std::endl;
}

void TimeSeries::PrintMax(){
    if(array_used_capacity == 0 || !IntegrateFlag){
        std::cout <<"Failure" <<std::endl;
    }else{
        double maxspeed = speed_array[0].magnitude;
        std::size_t maxindex = 0;
        for(std::size_t i{1}; i < array_used_capacity; i++){
            if(speed_array[i].magnitude > maxspeed){
                maxspeed = speed_array[i].magnitude;
                maxindex = i;
            }
        }
        std::cout << "Max Speed: " << maxspeed << " m/s" << std::endl;
        std::cout << "Time of Max Speed: " << (double)maxindex*time_interval << " s" << std::endl;
    }
}

void TimeSeries::CalcErr(){
    std::ifstream csvfile(calfile);
    std::string csvStringElement;
    std::string acc_x;
    std::string acc_y;
    std::string acc_z;
    long long x{0};
    long long y{0};
    long long z{0};
    int min_x{INT_MAX};
    int max_x{INT_MIN};
    int min_y{INT_MAX};
    int max_y{INT_MIN};
    int min_z{INT_MAX};
    int max_z{INT_MIN};

    std::size_t n{0};
    while(std::getline(csvfile,csvStringElement)){
        std::stringstream ss(csvStringElement);
        std::getline(ss,acc_x,',');
        std::getline(ss,acc_y,',');
        std::getline(ss,acc_z);
        int temp_x = std::stoi(acc_x) - g_offset;
        int temp_y = std::stoi(acc_y);
        int temp_z = std::stoi(acc_z);
        if(temp_x < min_x){
            min_x = temp_x;
        }
        if(temp_x > max_x){
            max_x = temp_x;
        }
        if(temp_y < min_y){
            min_y = temp_y;
        }
        if(temp_y > max_y){
            max_y = temp_y;
        }
        if(temp_z < min_z){
            min_z = temp_z;
        }
        if(temp_z > max_z){
            max_z = temp_z;
        }
        x += temp_x;
        y += temp_y;
        z += temp_z;
        n++;
    }
    offset_x = ((double)x /(double)n) * scalar;
    offset_y = ((double)y /(double)n) * scalar;
    offset_z = ((double)z /(double)n) * scalar;
    std::cout << "error calculated!" << std::endl;
    std::cout << "x Bias: " << offset_x << " m/s^2" << std::endl;
    std::cout << "x Variance: " << (double)(max_x - min_x)*scalar << " m/s^2" << std::endl;

    std::cout << "y Bias: " << offset_y << " m/s^2" << std::endl;
    std::cout << "y Variance: " << (double)(max_y - min_y)*scalar << " m/s^2" << std::endl;

    std::cout << "z Bias: " << offset_z << " m/s^2" << std::endl;
    std::cout << "z Variance: " << (double)(max_z - min_z)*scalar << " m/s^2" << std::endl;
}

void TimeSeries::doubleArray(){
    speed_data* temp = speed_array;
    acceleration_data* tempacc = acceleration_array;
    speed_array = new speed_data[array_size * 2];
    acceleration_array = new acceleration_data[array_size * 2];
    array_size = array_size * 2;
    for(std::size_t i = 0; i < array_used_capacity; i++){
        speed_array[i] = temp[i];
        acceleration_array[i] = tempacc[i];
    }
    temp = nullptr;
    tempacc = nullptr;
}

double TimeSeries::VectorMagnitude(std::size_t index){
    return sqrt((speed_array[index].x * speed_array[index].x + 
    speed_array[index].y * speed_array[index].y + speed_array[index].z * speed_array[index].z));
}

void TimeSeries::Trapezoidal(std::size_t index, double &x, double &y, double &z){
    x = speed_array[index -1].x + time_interval * (acceleration_array[index - 1].ax + acceleration_array[index].ax)/2.0;
    y = speed_array[index -1].y + time_interval * (acceleration_array[index - 1].ay + acceleration_array[index].ay)/2.0;
    z = speed_array[index -1].z + time_interval * (acceleration_array[index - 1].az + acceleration_array[index].az)/2.0;
}

void TimeSeries::Back4Pt(std::size_t index, double &x, double &y, double &z){
    double pone{acceleration_array[index].ax * 9.0/24.0};
    double ptwo{acceleration_array[index -1].ax * 19.0/24.0};
    double pthree{0.0};
    double pfour{0.0};

    if(index >= 2){
        pthree = acceleration_array[index -2].ax * -5.0/24.0;
    }
    if(index >= 3){
        pfour = acceleration_array[index -3].ax * 1.0/24.0;
    }
    x = speed_array[index -1].x + (pone + ptwo + pthree + pfour)*time_interval;

    pone = acceleration_array[index].ay * 9.0/24.0;
    ptwo = acceleration_array[index - 1].ay * 19.0/24.0;
    if(index >= 2){
        pthree = acceleration_array[index -2].ay * -5.0/24.0;
    }
    if(index >= 3){
        pfour = acceleration_array[index -3].ay * 1.0/24.0;
    }
    y = speed_array[index -1].y + (pone + ptwo + pthree + pfour)*time_interval;

    pone = acceleration_array[index].az * 9.0/24.0;
    ptwo = acceleration_array[index - 1].az * 19.0/24.0;
    if(index >= 2){
        pthree = acceleration_array[index -2].az * -5.0/24.0;
    }
    if(index >= 3){
        pfour = acceleration_array[index -3].az * 1.0/24.0;
    }
    z = speed_array[index -1].z + (pone + ptwo + pthree + pfour)*time_interval;
}