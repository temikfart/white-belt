#include <iostream>

using namespace std;

/*
string AskTimeServer() {
//  throw system_error(error_code());
  throw invalid_argument("");
  return "01:00:00";
}
*/

class TimeServer {
public:
  string GetCurrentTime() {
    string tmp = last_fetched_time;
    try {
      last_fetched_time = AskTimeServer();
    } catch (system_error const & ex) {
      last_fetched_time = tmp;
    } catch (exception & e) {
      throw;
    }
    return last_fetched_time;
  }
private:
  string last_fetched_time = "00:00:00";
};

int main() {
  TimeServer ts;
  try {
    cout << ts.GetCurrentTime() << endl;
  } catch (exception& e) {
    cout << "Exception got: " << e.what() << endl;
  }
  
  return 0;
}