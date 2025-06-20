#include <stdexcept>

using namespace std;

/**
 * @brief Exception thrown when a checksum validation fails.
 *
 * This exception indicates that a calculated checksum does not match the expected
 * checksum, suggesting data corruption or an invalid transmission.
 */
class ChecksumException : public std::exception
{
public:
    ChecksumException(const std::string &message) : message_(message) {}
    const char *what() const throw()
    {
        return message_.c_str();
    }

private:
    std::string message_;
};