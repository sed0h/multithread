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

#include <thread>
#include <iostream>

class ThreadObject {
  public:
    ThreadObject();
    ~ThreadObject();
    void threadFunc(const std::string &str, double d) {
        std::cout << "ThreadObject::threadFunc:str=" << str << "\t d=" << d << std::endl;
    }
    void operator()(const std::string &str, int i) {
        std::cout << "ThreadObject::operator():str=" << str << "\t i=" << i << std::endl;
    }

  private:
};

int main() {
    int score = 99;
    std::thread th1([&score]() { std::cout << "score = " << score << std::endl; });
    th1.join();

    ThreadObject to;
    std::thread  th2(&ThreadObject::threadFunc, &to, "xiaoming", 98);
    th2.join();

    std::thread th3(std::ref(to), "xiaohua", 97);
    th3.join();

    return 0;
}