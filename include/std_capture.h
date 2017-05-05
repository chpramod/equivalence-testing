#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

class StdCapture
{
public:
    StdCapture(): m_capturing(false), m_init(false), m_oldStdOut(0), m_oldStdErr(0);
    ~StdCapture();
    void BeginCapture();
    bool EndCapture();
    std::string GetCapture() const;

private:
    enum PIPES { READ, WRITE };
    int m_pipe[2];
    int m_oldStdOut;
    int m_oldStdErr;
    bool m_capturing;
    bool m_init;
    std::string m_captured;
};