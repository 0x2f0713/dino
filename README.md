# Dino

Dự án game Dino tương tự như trò chơi ẩn của Google Chrome, dự án chỉ hỗ trợ trên Linux

## Hướng dẫn cài đặt

### 1. Chạy trực tiếp từ binary



### 2. Build từ source code

#### Cài đặt Cmake
Dự án yêu cầu cài đặt Cmake phiên bản tối thiểu là 3.14. 

Với Ubuntu 20.04, bạn có thể cài đặt Cmake 3.16 bằng `apt`
```shell
sudo apt-get install cmake -y
```
Với Ubuntu 18.04 trở xuống, bạn cần cài Cmake từ [Kitware APT Repository](https://apt.kitware.com/) hoặc [build Cmake từ source](https://cmake.org/install/)

#### Hướng dẫn build game (sau khi cài đặt Cmake)
```shell
# Install required packages (without CMake)
sudo apt-get install git build-essential libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev -y
# Clone this repository
git clone https://github.com/0x2f0713/dino.git
# Change directory and build
cd dino
cmake -S . -B build
cd build
make
```

#### Chạy game
File excutable nằm trong thư mục `build` và có thể chạy trực tiếp bằng lệnh sau
```shell
./Dino
```

## Về trò chơi

Trò chơi được lấy cảm hứng từ trò chơi Dino của Google Chrome. Người chơi sẽ được nhập vai vào một chú khủng long phải vượt qua những chướng ngại vật phía trước càng nhiều càng tốt.

## Các chức năng

- Hiển thị hướng dẫn chơi khi khởi động game
- Tăng tốc độ sau mỗi 100 điểm đạt được
- Nhảy với tốc độ nhảy thay đổi theo gia tốc cố định
- Có thể chơi lại sau khi thua
- Có âm thanh khi đạt mỗi mốc 100 điểm, thực hiện nhảy và khi va chạm chướng ngại vật
- Lưu điểm số cao nhất của những lần chơi

Demo Video: comming soon...

## Các kỹ thuật lập trình được sử dụng

- Sử dụng struct để thể hiện ngữ cảnh (context) và các chướng ngại vật (enemy)
- Sử dụng namespace để xây dựng thư viện xử lý đồ họa, âm thanh, tích hợp thư viện vào gameplay để code được hệ thống hóa
- Sử dụng con trỏ để thao tác với vùng nhớ và SDL2
- Sử dụng các cấu trúc dữ liệu như mảng, deque để lưu vị trí của những đối tượng trong game

## Kết luận

<!-- Dự án game tương đối sơ sài về đồ họa khi sử dụng hình ảnh các đối tượng từ game của Google Chrome -->
**Kết quả của dự án**: Game chạy được như mong muốn, đúng mô tả, tuy nhiên đồ họa không được xuất sắc khi hình ảnh được lấy trực tiếp từ game trên Google Chrome.

**Hướng phát triển tiếp theo:**
- Cải thiện hình ảnh của các đối tượng.
- Triển khai chế độ multiplayer qua mạng internet (Sử dụng UDP để giao tiếp với server)
- Thêm những level vào game để game thêm thú vị
- Sử dụng ninja để tăng tốc độ build game khi game có nhiều target cần build

**Điều tâm đắc rút ra sau khi hoàn thành chương trình:**
- Bước đầu sử dụng được Cmake để generate Makefile, quản lý được dependenies, giúp cho quá trình build và debug game được dễ dàng hơn
- Áp dụng [The Pitchfork Layout](https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs) giúp quản lý project trở nên dễ dàng, thuận lợi và nhanh chóng.
- Có thể tách được các thành phần nhỏ như GamePlay, quản lý UI thành các library để module hóa chương trình.