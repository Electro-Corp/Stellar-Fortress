#ifndef SIZE_H
#define SIZE_H

class Size {
public:
    Size();
    Size(int x, int y);

    // Getter methods
    int getX() const;
    int getY() const;

    // Setter methods
    void setX(int x);
    void setY(int y);

private:
    int x_;
    int y_;
};

#endif // SIZE_H
