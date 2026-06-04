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
        acceleration_array[array_used_capacity].ax = (double)acceleration_array[array_used_capacity].x * scalar - offset_x;
        acceleration_array[array_used_capacity].ay = (double)acceleration_array[array_used_capacity].y * scalar - offset_y;
        acceleration_array[array_used_capacity].az = (double)acceleration_array[array_used_capacity].z * scalar - offset_z;
    }
    std::cout <<"************ " <<std::endl;
    std::cout << "Scalar and Offset Calculated!" << std::endl;
    std::cout << "Success" << std::endl;
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