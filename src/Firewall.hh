#pragma once
#include "Application.hh"
#include "Loader.hh"
#include "SwitchConnectionFwd.hh"
#include "Common.hh"

class Firewall : public Application {
SIMPLE_APPLICATION(Firewall, "firewall")
public:
    void init(Loader* loader, const Config& config) override;

};
