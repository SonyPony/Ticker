//
// Created by Sony on 13.11.2018.
//

#ifndef ISA_TICKER_H
#define ISA_TICKER_H

#include <functional>
#include <chrono>
#include <future>


class Ticker {
    private:
        std::promise<void> m_exitSignal;

    public:
        template <typename callable, typename... arguments, typename time>
        std::thread run(time after, callable&& f, arguments&&... args) {
            std::function<typename std::result_of<callable(arguments...)>::type()> task{
                    std::bind(std::forward<callable>(f), std::forward<arguments>(args)...)};

            return std::thread([after, task, this]() {
                std::future<void> futureExit = m_exitSignal.get_future();

                while(futureExit.wait_for(after) == std::future_status::timeout)
                    task();
            });
        };

        void stop();
};


#endif //ISA_TICKER_H
