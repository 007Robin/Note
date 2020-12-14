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

如何实现 线程安全？
