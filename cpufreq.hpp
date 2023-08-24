#include <set>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>


namespace cpufreq_cpp{
namespace fs = std::filesystem;
struct Unit { 
    std::string name;
    std::string path;
    double freq;
    std::string readed;
};
class Reader{
  private:
    std::vector<Unit> units;
    std::string policyDir (int &serial){
        return (
            "/sys/devices/system/cpu/cpufreq/policy"+
            std::to_string(serial)
        );
    };
    std::string policyScaleFile (int &serial){
        return (
            this->policyDir(serial)+
            "/scaling_cur_freq"
        );
    };
    void add(int &serial){
        Unit next;
        next.path = this->policyScaleFile(serial);
        next.name = next.path;
        this->units.push_back(next);
    };
    void read(int &serial){
        std::string readed;
        std::ifstream freq_file;
        freq_file.open(this->units[serial].path);
        std::getline(freq_file, readed);
        this->units[serial].freq = (std::stod(readed) / 1000000.00);
        this->units[serial].readed = readed;
        freq_file.close();
    };
  public:
    void discovery(){
        for (int i{0}; i < 256; i++)
            if(
                fs::exists(this->policyDir(i)) &&
                fs::exists(this->policyScaleFile(i))
            ){
                this->add(i);
            } else {
                break;
            }
    };
    void refresh(){
        for (int i{0}; i < this->units.size(); i++)
            this->read(i);
    };
    Unit get(int elem){
        Unit freq;
        if(
            elem < 0 ||
            elem >= this->units.size()
        )
            return freq;
        freq = this->units[elem];
        return freq;
    };
    std::vector<Unit> get(int start, int end){
        std::vector<Unit> freqs;
        if(
            start < 0 ||
            start > end ||
            start >= this->units.size() ||
            end >= this->units.size()
        )
            return freqs;
        for (int i{start}; i < this->units.size(); i++)
            freqs.push_back(this->units[i]);
        return freqs;
    };
    std::vector<Unit> get(std::vector<int> elements){
        std::vector<Unit> freqs;
        for (int i{0}; i < elements.size(); i++)
            freqs.push_back(this->get(i));
        return freqs;
    };
    std::vector<Unit> getAll(){
        return this->units;
    };
    double freq(int elem){
        double freq;
        if(
            elem < 0 ||
            elem >= this->units.size()
        )
            return freq;
        freq = this->units[elem].freq;
        return freq;
    };
    std::vector<double> freq(int start, int end){
        std::vector<double> freqs;
        if(
            start < 0 ||
            start > end ||
            start >= this->units.size() ||
            end >= this->units.size()
        )
            return freqs;
        for (int i{start}; i < end; i++)
            freqs.push_back(this->units[i].freq);
        return freqs;
    };
    std::vector<double> freq(std::vector<int> elements){
        std::vector<double> freqs;
        for (int i{0}; i < elements.size(); i++)
            freqs.push_back(this->freq(i));
        return freqs;
    };
    std::vector<double> freqAll(){
        std::vector<double> freqs;
        for (int i{0}; i < this->units.size(); i++)
            freqs.push_back(this->units[i].freq);
        return freqs;
    };
};
}
