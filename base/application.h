
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

class Application {
 public:
  Application();
  ~Application();
  bool Initialize();
  void Run();

 private:
  void Close();
};

#endif // __APPLICATION_H__