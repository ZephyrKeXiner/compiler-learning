#ifndef clox_scanner_h
#define clox_scanner_h

class Scanner
{
private:
  const char* start;
  const char* current;
  int line;
public:
  Scanner(/* args */);
  ~Scanner();
};

#endif