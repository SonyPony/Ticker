//
// Created by Sony on 13.11.2018.
//

#include "ticker.h"

void Ticker::stop() {
    m_exitSignal.set_value();
}
