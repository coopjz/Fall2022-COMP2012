# Initializers

An initializer specifies the initial value of a variable. You can initialize variables in these contexts:

- In the definition of a variable:

  ```cpp
  int i = 3;
  Point p1{ 1, 2 };
  ```

- As one of the parameters of a function:

  ```cpp
  set_point(Point{ 5, 6 });
  ```

- As the return value of a function:

  ```cpp
  Point get_new_point(int x, int y) { return { x, y }; }
  Point get_new_point(int x, int y) { return Point{ x, y }; }
  ```

Initializers may take these forms:

- An expression (or a comma-separated list of expressions) in parentheses:

  ```cpp
  Point p1(1, 2);
  ```

- An equals sign followed by an expression:

  ```cpp
  string s = "hello";
  ```

- A braced initializer list. The list may be empty or may consist of a set of lists, as in the following example:

  ```cpp
  struct Point{
      int x;
      int y;
  };
  class PointConsumer{
  public:
      void set_point(Point p){};
      void set_points(initializer_list<Point> my_list){};
  };
  int main() {
      PointConsumer pc{};
      pc.set_point({});
      pc.set_point({ 3, 4 });
      pc.set_points({ { 3, 4 }, { 5, 6 } });
  }
  ```

# Kinds of initialization

>  There are several kinds of initialization, which may occur at different points in program execution.

> Different kinds of initialization are not mutually exclusive. for example, list initialization can trigger value initialization and in other circumstances, it can trigger aggregate initialization.

