#include <memory>
#include <vector>
#include "cpufreq.hpp"

int main(){
    std::vector<double> freqs;
    std::shared_ptr<cpufreq_cpp::Reader> freq (new cpufreq_cpp::Reader());
    freq->discovery();
    freq->refresh();
    freqs = freq->freqAll();
    for (int i{0}; i < freqs.size(); i++)
        std::cout << freqs[i] << std::endl;
}
