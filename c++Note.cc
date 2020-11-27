polymorphism        : send messages to different objects, executed diff method at runtime。
inheritance         : compile time识别class之间的inheritance(public,private,protect...)关系，polymorphism object关系在run time识别。

function vs. method : method只在你call时才take memory。

objects hold values/are instance of a class

friend vs method: 
when invoke a member function, it retreives a pointer to the object receving message。
call method时(&object, int, int) 隐含传的是（A* this, int, int)。
friend则 No this pointer, object is passed explicity。

explicit关键字用到时，会取消一切隐含转换, 如函数参数中auto call constructor, (string)"hello"中char[]转成char*
noexcept关键字，说明保证all correct, 让compiler最大去优化
constexpr关键字，说明everything init at compiler time, NO runtime.

delegating constructors:    用一个constructor去construct另一个constructor，避免了code repetition
constexpr constructor xx() const noexcept

Astring *str = new Astring("hello");
*str在stack上  pointing to --->   在heap上的hello

stactic member function 可access static var/fuc，不可access instance var/fuc

