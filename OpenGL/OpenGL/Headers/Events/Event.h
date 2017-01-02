#pragma once

#include <functional>
#include <vector>


namespace OpenGL
{

template <typename ReturnType, typename ArgType>
class Event
{
  private:
    typedef std::function<ReturnType(ArgType)> Function;

  public:
    void subscribe(const Function& callback) { m_callbacks.push_back(callback); }
    void unsubscribe(const Function& callback) { ASSERT_FAIL(); }
    void invoke(ArgType arg);

  private:
    std::vector<Function> m_callbacks;
};

//------------------------------------------------------------------------------------------------
template <typename ReturnType, typename ArgType>
void Event<ReturnType, ArgType>::invoke(ArgType arg)
{
  for (const Function& func : m_callbacks)
  {
    func(arg);
  }
}

}