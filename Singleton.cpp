//单例模式保证一个类仅有一个实例，并提供一个访问它的全局访问点，该实例被所有程序模块共享。
template <typename T>
class Instance
{
public:
  static T& Instance()
  {
    if (!data_)
      data_ = new T();
    return *data_;
  }
  
private:
  static T* data_;
  
};

//如何实现 线程安全？
//https://wangpifu.github.io/post/singleton-dan-li-mo-shi/
//我们在函数内部定义一个局部静态变量(local static)，它只有在instance第一次被使用时才会创建实例。c++11 也规定了local static是线程安全的
//一个简单的实现：
template<typename T>
T& instance()
{
    static std::unique_ptr<T> instance{new T{}};
    return *instance;
}

template<typename T>
class Singleton
{
protected:
    Singleton() noexcept = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    // to silence base class Singleton<T> has a non-virtual destructor [-Weffc++]
    virtual ~Singleton() = default; 

public:
    static T& get_instance() noexcept(std::is_nothrow_constructible<T>::value)
    {
        // Guaranteed to be destroyed. Instantiated on first use. Thread safe in C++11
        static T instance;
        return instance;
    }
};
class TradeServer : public Singleton<TradeServer>
{
  //...
}
