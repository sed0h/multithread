//#include <iostream>
//#include <thread>
//
//void threadFunc(std::string &str, int a) {
//    str = "changed by threadFunc";
//    a   = 13;
//}
//
//int main(){
//    std::string str("main");
//    int         a = 9;
//	std::thread th(threadFunc, std::ref(str), a);
//
//    th.join();
//
//    std::cout << "str=" << str << std::endl;
//    std::cout << "a=" << a << std::endl;
//
//	return 0;
//}

//创建线程例子
//#include <thread>
//#include <iostream>
//#include <string>
//
//class ThreadObject {
//  public:
//    void threadFunc(const std::string &str, double d) {
//        std::cout << "ThreadObject::threadFunc:str=" << str << "\t d=" << d << std::endl;
//    }
//    void operator()(const std::string &str, int i) {
//        std::cout << "ThreadObject::operator():str=" << str << "\t i=" << i << std::endl;
//    }
//
//  private:
//};
//
//int main() {
//    int score = 99;
//    std::thread th1([&score]() { std::cout << "score = " << score << std::endl; });
//    th1.join();
//
//    ThreadObject to;
//    std::thread  th2(&ThreadObject::threadFunc, &to, "xiaoming", 98);
//    th2.join();
//
//    std::thread th3(std::ref(to), "xiaohua", 97);
//    th3.join();
//
//    return 0;
//}

//lock_guard
//#include <thread>
//#include <mutex>
//#include <vector>
//#include <iterator>
//#include <iostream>
//
//std::mutex g_mutex;
//void doThreadFunc(int n, char c) {
//    //g_mutex.lock();
//    //std::vector<int> vec(n, c);
//    //std::copy(vec.begin(), vec.end(), std::ostream_iterator<char>(std::cout, ""));
//    //std::cout << std::endl;
//    //
//    //g_mutex.unlock();
//
//    std::lock_guard<std::mutex> lg(g_mutex);
//    std::vector<int> vec(n, c);
//    std::copy(vec.begin(), vec.end(), std::ostream_iterator<char>(std::cout, ""));
//    std::cout << std::endl;
//}
//
//template <typename ... Args>
//void threadFunc(Args && ... args) {
//    try {
//        doThreadFunc(std::forward<Args>(args)...);
//    } catch (const std::exception &) {}
//}
//int main() {
//    std::thread th1([] { threadFunc(10, '*'); });
//    std::thread th2([] { threadFunc(5, '#'); });
//
//    th1.join();
//    th2.join();
//
//    return 0;
//}

//unique lock
//#include <random>
//#include <time.h>
//#include <mutex>
//#include <iostream>
//#include<numeric>
//
//std::mutex g_mutex;
//
//void threadFunc(size_t num) {
//    static std::default_random_engine random(time(nullptr));
//    static std::uniform_int_distribution<int> dist(0, 100);//离散均匀分布
//
//     std::vector<int> vec;
//    vec.reserve(num);
//
//    std::unique_lock<std::mutex> ul(g_mutex);
//    std::generate_n(std::back_inserter(vec), num, [] { return dist(random); });//lambda表达式
//
//    ul.unlock();
//
//    int sum = std::accumulate(vec.begin(), vec.end(), 0);
//    double avg = 1.0 * sum / vec.size();
//
//    ul.lock();
//    std::cout << "thread id " << std::this_thread::get_id() << "obtains avg num =" << avg
//              << std::endl;
// }
//
//int main() {
//     std::thread th1(threadFunc, 100);
//    std::thread th2(threadFunc, 200);
//
//     th1.join();
//    th2.join();
//
//    return 0;
//}

//条件变量
//#include <mutex>
//#include <condition_variable>
//#include <list>
//#include <iostream>
//
//std::mutex              g_mutex;
//std::condition_variable cond;
//std::list<int>          alist;
//
//void threadFun1() {
//    std::unique_lock<std::mutex> ul(g_mutex);
//    while (alist.empty()) {
//        cond.wait(ul);
//    }
//    std::cout << "threadFun1 get the value : " << alist.front() << std::endl;
//    alist.pop_front();
//}
//
//void threadFun2() {
//    std::lock_guard<std::mutex> lg(g_mutex);
//    alist.push_back(13);
//
//    cond.notify_one();
//}
//
//int main() {
//    std::thread th1(threadFun1);
//    std::thread th2(threadFun2);
//
//    th1.join();
//    th2.join();
//
//    return 0;
//}

//线程函数返回值
//#include <future>
//#include <iostream>
//#include <numeric> 
//#include <vector>
//
//void threadFun(const std::vector<int> &big_vec, std::promise<double> prom) {
//    double sum = std::accumulate(big_vec.begin(), big_vec.end(), 0.0);
//
//    double avg = 0;
//    if (!big_vec.empty())
//        avg = sum / big_vec.size();
//
//    prom.set_value(avg);
//}
//
//int main() {
//    std::promise<double> prom;
//    std::future<double>  fu = prom.get_future();
//
//    std::vector<int> vec{1, 2, 3, 4, 5, 6};
//    std::thread      th(threadFun, std::ref(vec), std::move(prom));
//    th.detach();
//    
//    double avg =
//        fu.get(); // std::promise和std::future配套使用，往std::promise变量写入值，就能从其关联的std::future变量获取写入的值
//    std::cout << "avg = " << avg << std::endl;
//
//	return 0;
//}

// std::async
#include <vector>
#include <future>
#include <numeric>
#include <iostream>
double calcAvg(const std::vector<int> &vec) {
    double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
    double avg = 0;
    if (!vec.empty()) {
        avg = sum / vec.size();
    }
    return avg;
}

int main() {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::future<double> fu = std::async(calcAvg, std::ref(vec));

    double              avg = fu.get();
    std::cout << "avg = " << avg << std::endl;

	return 0;
}