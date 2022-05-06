#include <iostream>

#include <functional>
#include <memory>
#include <unordered_map>

namespace Internal {

typedef std::string TypeId;

struct Delegate
{
  virtual ~Delegate() {}
};

template<typename T>
static TypeId
typeId()
{
  return typeid(T).name();
}

typedef std::unordered_map<TypeId, std::shared_ptr<Delegate>> TypeMap;

}

class CDispatcher
{
public:
  template<typename T>
  using Function = std::function<void(const T&)>;

  template<typename T, typename Handler>
  void addHandler(Handler handler)
  {
    auto key = Internal::typeId<T>();
    auto wrapper = std::make_shared<FunctionContainer<T>>(handler);

    m_handlers[key] = wrapper;
  }

  template<typename T>
  void process(const T& data)
  {
    auto key = Internal::typeId<T>();
    auto it = m_handlers.find(key);

    if (it == m_handlers.end()) {
      std::cerr << "There is no handler for " << typeid(T).name();
      return;
    }

    auto wrapper = it->second.get();
    auto container = static_cast<FunctionContainer<T>*>(wrapper);

    return container->function(data);
  }

private:
  template<typename T>
  struct FunctionContainer : Internal::Delegate
  {
    Function<T> function;
    FunctionContainer(Function<T> _function)
      : function(_function)
    {}
  };

  Internal::TypeMap m_handlers;
};

using namespace std;

struct AEvent
{
  std::string name;
};

struct Cmd
{
  int cmd;
};

template<typename Command>
class ICommandHandler
{
public:
  virtual void Handle(const Command&) = 0;
};

class MyExcelentCommandHandler : public ICommandHandler<Cmd>
{
public:
  void Handle(const Cmd& data) { cout << "Really handle:" << data.cmd << endl; }
};

int
main(int argc, char* argv[])
{
  CDispatcher dispatcher;

  cout << "Hello World!" << endl;

  dispatcher.addHandler<AEvent>(
    [](const AEvent& data) { cout << "Handle:" << data.name << endl; });

  dispatcher.addHandler<Cmd>([](const Cmd& data) {
    MyExcelentCommandHandler handler;
    handler.Handle(data);
    ;
  });

  dispatcher.process(AEvent{ "this new event" });
  dispatcher.process(Cmd{ 50 });
  return 0;
}
