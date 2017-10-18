#include <iostream>
#include <memory>

using namespace std;

class CMachine;

class CState {
 public:
  virtual ~CState() = default;

  virtual void on(shared_ptr<CMachine>) {
    cout << " already ON\n";
  }

  virtual void off(shared_ptr<CMachine>) {
    cout << " already OFF\n";
  }
};

class COn : public CState {
 public:
  COn() {
    cout << " COn-ctor ";
  }

  ~COn() override {
    cout << " COn-dtor\n";
  }

  void off(shared_ptr<CMachine> machine) override;
};

class COff : public CState {
 public:
  COff() {
    cout << " COff-ctor ";
  }

  ~COff() override {
    cout << " COff-dtor\n";
  }

  void on(shared_ptr<CMachine> machine) override;
};

class CMachine : public enable_shared_from_this<CMachine> {
 public:
  CMachine() : m_currentState(make_unique<COff>()) {
    cout << '\n';
  }

  void setCurrent(unique_ptr<CState> state) {
    m_currentState = move(state);
  }

  void on() {
    m_currentState->on(shared_from_this());
  }

  void off() {
    m_currentState->off(shared_from_this());
  }

 private:
  unique_ptr<CState> m_currentState;
};

void COn::off(shared_ptr<CMachine> machine) {
  cout << " going from ON to OFF\n";
  machine->setCurrent(make_unique<COff>());
}

void COff::on(shared_ptr<CMachine> machine) {
  cout << " going from OFF to ON\n";
  machine->setCurrent(make_unique<COn>());
}

int main() {
  auto machine = make_shared<CMachine>();
  machine->on();
  machine->off();
  machine->off();
  machine->on();
}
