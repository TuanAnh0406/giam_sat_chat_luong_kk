# 🌫️ Mạng lưới giám sát chất lượng không khí thành phố

## 📌 Giới thiệu

Hệ thống mạng lưới cảm biến giám sát chất lượng không khí là một giải pháp hiện đại nhằm theo dõi tình trạng môi trường đô thị theo thời gian thực. Mỗi trạm cảm biến được triển khai tại nhiều vị trí khác nhau trong thành phố, giúp thu thập dữ liệu về bụi mịn (PM2.5), khí độc (CO, NH3,...), nhiệt độ và độ ẩm. 

Dữ liệu được gửi về **Firebase Realtime Database**, sau đó hiển thị trực quan trên bản đồ giúp người dân và cơ quan chức năng dễ dàng theo dõi mức độ ô nhiễm không khí và đưa ra cảnh báo khi cần thiết.

## 🧠 Mục tiêu

- Giám sát chất lượng không khí ở cấp độ khu vực theo thời gian thực.
- Tăng cường cảnh báo sớm về các nguy cơ ô nhiễm.
- Hỗ trợ cơ quan chức năng và người dân trong việc bảo vệ sức khỏe.
- Góp phần xây dựng thành phố thông minh và xanh.

## ⚙️ Công nghệ sử dụng

| Thành phần               | Mô tả |
|--------------------------|-------|
| **NodeMCU ESP8266**      | Vi điều khiển, gửi dữ liệu đo được qua WiFi |
| **Cảm biến PM2.5**       | Đo nồng độ bụi mịn trong không khí |
| **Cảm biến MQ-135**      | Đo khí độc như CO, NH3, NOx,... |
| **Cảm biến DHT22**       | Đo nhiệt độ và độ ẩm |
| **Firebase Realtime DB** | Lưu trữ và đồng bộ dữ liệu giám sát |
| **Firebase Hosting**     | Hiển thị dữ liệu lên bản đồ theo thời gian thực |
| **Google Maps API**      | Trực quan hóa vị trí và chỉ số không khí theo từng điểm đo |

## 🔄 Quy trình hoạt động

1. Trạm cảm biến tại các điểm đo thu thập dữ liệu định kỳ.
2. NodeMCU xử lý và gửi dữ liệu lên Firebase.
3. Web app lấy dữ liệu từ Firebase để hiển thị lên bản đồ.
4. Khi chỉ số không khí vượt ngưỡng, hệ thống cảnh báo trực tuyến.

## 📍 Tính năng nổi bật

- Giám sát không khí theo thời gian thực.
- Hiển thị dữ liệu trực quan trên bản đồ.
- Cảnh báo ô nhiễm tự động.
- Mở rộng dễ dàng các trạm đo trong thành phố.

## 🔮 Định hướng phát triển

- Tích hợp AI để dự đoán diễn biến ô nhiễm.
- Thêm cảm biến đo CO2, NO2, SO2,...
- Phát triển ứng dụng di động cho người dân theo dõi tức thì.
- Cho phép người dân gửi phản ánh về môi trường.

---

> 👨‍💻 **Tác giả:** Nguyễn Tuấn Anh 
