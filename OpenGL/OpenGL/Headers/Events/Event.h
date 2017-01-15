#pragma once

#include <functional>
#include <vector>


namespace OpenGL
{

/// \brief Currently we only support one argument and no return type
/// How do we extend this to a return type if we have multiple possible invokers
template <typename ArgType>
class Event
{
  private:
    typedef std::function<void(ArgType)> Function;

  public:
    void subscribe(const Function& callback) { m_callbacks.push_back(callback); }
    void unsubscribe(const Function& callback) { ASSERT_FAIL(); }
    void invoke(ArgType arg);

  private:
    std::vector<Function> m_callbacks;
};

//------------------------------------------------------------------------------------------------
template <typename ArgType>
void Event<ArgType>::invoke(ArgType arg)
{
  for (const Function& func : m_callbacks)
  {
    func(arg);
  }
}

}