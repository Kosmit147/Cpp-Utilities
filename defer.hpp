#include <concepts>
#include <utility>
#include <functional>

template<std::regular_invocable Func> class Defer
{
public:
    explicit Defer(Func&& func) : _func{ std::forward<decltype(func)>(func) } {}

    ~Defer()
    {
        if (!_dismissed)
            std::invoke(_func);
    }

    Defer(const Defer&) = delete;
    auto operator=(const Defer&) = delete;
    Defer(Defer&&) = delete;
    auto operator=(Defer&&) = delete;

    auto dismiss() -> void { _dismissed = true; }

private:
    Func _func;
    bool _dismissed = false;
};