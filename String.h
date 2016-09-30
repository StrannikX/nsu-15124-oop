#ifndef STRING_H
#define STRING_H


class String
{
    public:
        String();
        String(const char*);
        String(const String&);

        virtual ~String();

        int length() const;
    protected:
    private:
        int len;
        char *str;

    public:
        operator char*() const;
        char& operator[](int);
        String& operator=(const String&);

        friend String operator+(const String&, const String&);
        friend String& operator+=(String&, const String&);
};

String operator+(const String&, const String&);
String& operator+=(String&, const String&);

#endif // STRING_H
