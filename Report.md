# BÁO CÁO VỀ ĐO CHIỀU CAO CỦA CÂY
#### Họ và tên: Vũ Tiến Giáp
#### MSSV: 22520367

## 1. AVL Tree
- Là cây tìm kiếm nhị phân **(BST)** có tính chất tự cân bằng.
- Tại mỗi nút của nó độ cao của cây con trái và của cây con phải **chênh lệch không quá một**.
- Với một cây AVL có N nút, chiều cao của cây sẽ là **log(N)**
- Đối với một cây AVL, **chỉ số cân bằng** của một nút là hiệu của chiều cao cây con phải và cây con trái của nó. Đối với một cây cân bằng, chỉ số cân bằng **chỉ** có thể nhận được một trong ba giá trị là -1, 1, 0
- Ngoài các thao tác bình thường trong cây nhị phân tìm kiếm, các thao tác đặc trưng của cây AVL bao gồm:
    + Thêm một phần tử vào cây AVL
    + Hủy một phân từ trên cây AVL
    + Cân bằng lại một cây vừa mất cân bằng
- Mỗi lượt chèn hoặc xóa một nút nếu xảy ra mất cân bằng thì có thể xảy ra một trong bốn trường hợp sau:
    + Left Left Case
    + Left Right Case
    + Right Right Case
    + Right Left Case
- Code cài đặt có trong file `AVL_Tree.cpp`

## 2. Red Black Tree
- Được phát triển từ cây AVL
- Các tính chất **đặc trưng** của cây đỏ đen bao gồm:
    + Mọi nút đều phải có màu **đỏ** hoặc **đen**
    + **Nút gốc (root)** **luôn** phải có màu **đen**
    + **Không** có 2 nút đỏ **liền kề** (Một nút đỏ thì không thể có cha đỏ hoặc con đỏ)
    + Mọi đường dẫn từ một node đến bất kì node NULL (thuộc con của nó ) thì đều có **cùng số lượng node đen**.
    + **Tất cả** các node lá (NULL) đều **màu đen**.
- Đối với một cây đỏ đen có N nút, chiều cao của cây luôn nhỏ hơn **2*log(N+1)** 
- Các thao tác trên cây đỏ đen cũng tương tự như cây nhị phân tìm kiếm thông thường. Tuy nhiên ta cần chú ý đến màu của các nút để không vi phạm các tính chất
- Tuy có cấu trúc phức tạp, nhưng cây đỏ đen luôn đảm bảo một thời gian tốt nhất trong trường hợp xấu nhất cho các phép toán **chèn (insertion)**, **xóa (deletion)**,và **tìm kiếm (search)** 
- Code cài đặt có trong file `RB_Tree.cpp`
## 3. Tổng kết
- Cây AVL **cân bằng hơn** cây đỏ đen do khi thực hiện quá trình chèn hoặc xóa, cây AVL sẽ quay (cân bằng) **liên tục**.
- Nhưng vì việc quay liên tục để giữ cân bằng nên khi có càng nhiều phần tử thì việc cân bằng cây sẽ **lâu** hơn. Chính vì vậy nếu dữ liệu đầu vào lớn thì ta nên ưu tiên cây đỏ đen, ngược lại thì ưu tiên cây AVL
- Bảng so sánh chiều cao giữa 2 cây:



| Test | AVL Tree | RB Tree |
|:----:|:--------:|:-------:|
|  1   |    23    |   25    |
|  2   |    23    |   38    |
|  3   |    23    |   38    |
|  4   |    23    |   38    |
|  5   |    23    |   38    |
|  6   |    23    |   38    |
|  7   |    23    |   38    |
|  8   |    23    |   38    |
|  9   |    23    |   38    |
|  10  |    23    |   38    |

