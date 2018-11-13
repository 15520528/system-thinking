# README
## I. Các khái niệm
1. Performance vs scalability
- <b>Performance ( Hiệu suất) </b> ám chỉ đến khả năng làm việc của một system I, ví dụ như nó có thể xử lý một request trong thời gian bao lâu (responese time) , số lượng request mà system đó có thể xử lý trong một khoảng thời gian (throughput)
-  Khi performance của system thay đổi ( ví dụ như system phải phục vụ thêm user, hoặc thời gian sesponse giảm đi), lúc này để tăng hiệu suất  thì ta nói đến Scalability.
- <b>Scalability </b> là khả năng của một hệ thống có thể tăng performance bằng cách thêm các resources (server, cpu, ram  ...). Bất kể bao nhiêu hardware được thêm vào nhưng có thể quan sát được performance sẽ được tăng.

 2. cách tiếp cận với scalability

- <b>2.1 Vertical scaling : </b> Là phương pháp tăng khả năng chịu tại trên một nodes (nodes ở đây có thể là server), thêm các hardware reosurce cho một nodes. 
-   Ưu điểm: Không cần phải thay đổi lại kiến trúc hệ thống, 
-  Nhược điểm: Khả năng scalability bị ràng buộc với phần cứng tại mọi thời điểm

    ![image](images/verticalscaling.png)

- <b> 2.2 horizontal scaling</b> Là phương pháp tăng tải của system bằng cách tăng thêm nodes. Bằng cách tiếp cận này, requests từ user sẽ được phân phối tới các nodes này. 
- ưu điểm: Xử lý được nhiều request trong một khoảng thời gian 
- Nhược điểm: cách tiếp cận này yêu cầu phải thiết kế sao cho các nodes phải xử lý các request đồng đều.
2. Latency vs throughput
- Latency is the time required to perform some action or to produce some result. Latency is measured in units of time -- hours, minutes, seconds, nanoseconds or clock periods. 
- Throughput is the number of such actions executed or results produced per unit of time. This is measured in units of whatever is being produced (cars, motorcycles, I/O samples, memory words, iterations) per unit of time. The term "memory bandwidth" is sometimes used to specify the throughput of memory systems.
3. Định lý CAP

    3.1 Định nghĩa
- Định lý CAP là định lý được Eric Brew viết năm 2002 nhằm đề xuất các quy luật cho hệ thống phân tán. Trong quy trình xây dựng 1 hệ thống phân tán bạn chỉ có thể chọn 2 trong 3 tính chất sau đây để xây dựng:
    * <b>Consistency (tính nhất quán về dữ liệu)</b> Trong hệ thống phân tán, dữ liệu giữa các nodes (server) phải được đồng nhất với nhau tại mọi thời điểm. Bất kể hành động read data sẽ đều trả về gíá trị của bản ghi write mới nhất.
    * <b> Availability (tính sẵn sàng của server)</b> Trong hệ thống phân tán, mỗi request đều nhận được một response. Avalability có được bằng cách hệ thống phải hoạt động bất kể mọi thời điểm. Mỗi client đều nhận được một response bất kể trạng thái của các nodes trên hệ thống. 
    * <b>Partition Tolerance </b> Hệ thống vẫn tiếp tục hoạt động kể cả trong trường hợp một số thông điệp bị trì hoãn hoặc mất giữa các nodes. Một hệ thống là partition-tolerance  nếu có bất kì failure network thì vẫn  không dẫn đến failure trên toàn hệ thống. Khi xây dựng hệ thống phân tán, Partition Tolerance không phải là một lựa chọn, nó là điều cấp thiết. Do đó ta phải chuyển đổi dữa tính Consitency và Availability. Bởi vì ta không thể duy trì 1 hệ thống mà có đủ 3 tính chất PAC.

    ![cap](images/cap.png)
4.  consistency pattern
    4.1 Weak consistency
    -  Cách tiếp cận này được sử dụng trong các ứng dụng yêu cầu real time. như chat video, realtime mutilplayer games. Ví dụ trong game online, nếu bạn mất kết nối mạng trong vài giây thì sau khi kết nối lại, bạn sẽ không xem lại được chuyện gì xảy ra trong vài giây vừa rồi 
     
    4.2 Eventual Consistency
    - Cách tiếp cận này đảm bảo dữ liệu giữa các nodes cuối cùng sẽ đồng nhất với nhau. Thời gian để dữ liệu của các nodes đồng nhất với nhau là không thể xác định được.
    - Eventual Consistency đảm bảo dữ liệu đồng nhất nhưng trong quá trình đồng nhất thì nếu có một request read thì dữ liệu trả về có thể là dữ liệu cũ.
    ![even](images/enconsist.png)
    
    4.3 Strong Consistency
    - Cách tiếp cận này đảm bảo dữ liệu sẽ được đồng nhất với các nodes khác. Ngay khi có một write request gửi tới một trong số các nodes trên hệ thống. Trong khoảng thời gian dữ liệu trên các nodes được updated,  thì lúc này nếu có các write/read request cho dữ liệu này gửi đến bất kỳ nodes nào cũng sẽ bị delayed bời vì các nodes này đang phải đồng nhất dữ liệu này. Ngay sau khi dữ liệu này được đồng nhất, hệ thống sẽ xử lý các requests đã bị delayed
    - Strong consistency đảm bảo toàn bộ dữ liệu được đồng nhất nhưng high lantency

    ![strong](images/strongconsist.png)

5. Availability patterns

    5.1 Active-active 

    ![1](images/active.webp)

    - Một Cluster active-active trong thực tế thường được tạo ra bởi ít nhất 2 nodes, tất cả các nodes của cụm đều chạy đồng thời một dịch vụ cùng lúc. Mục đích chính của một active-active cluter là để cân bằng tải (load balancing). Load balancing phân phối workload giữa các node nhằm ngăn chặn tình trạng overloaded trên các nodes. Do đó, càng nhiều nodes phục vụ thì sẽ tăng throughput và response time.

    5.2 Active-passive 
    ![1](images/passive.webp)
     
    - Như cách mà active-active cluster phân cụm, active-passive cũng được tạo ra bởi ít nhất 2 nodes. Tuy nhiên, không phải tất cả các nodes đều hoạt động, nếu node đầu tiên hoạt động, thì node thứ 2 đứng gần không hoạt động. hay có thể nói nodes thứ 2 này là nodes dự phòng trong trường hợp nodes thứ nhất không hoạt động. 