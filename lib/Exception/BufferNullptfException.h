#include <stdexcept>

using namespace std;

/**
 * @brief Exception thrown when a null pointer is encountered for a buffer.
 *
 * This exception signifies an attempt to use a null pointer where a valid
 * memory buffer is expected, preventing potential crashes due to dereferencing
 * invalid memory.
 */
class BufferNulptrException : public std::exception
{
public:
    BufferNulptrException(const std::string &message) : message_(message) {}
    const char *what() const throw()
    {
        return message_.c_str();
    }

private:
    std::string message_;
};