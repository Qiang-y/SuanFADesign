import streamlit as st
import matplotlib.pyplot as plt
import time

# 判断数组是否是递增有序的
def is_increasing(arr):
    for i in range(len(arr) - 2):
        if arr[i] > arr[i + 1]:
            return False
    return True

class AutoMachine:
    output = -1
    state = 0
    point = 0
    Mid = -1    
    depth = 0   # 栈深度
    step = 0    # 步数

    # 第一次读取low和high
    def read_low_0(self, arr, work):
        self.step += 1
        global workPaperLen
        work[0] = arr[self.point]
        self.point += 1
        work[2] = arr[self.point]
        self.state = 1
        if workPaperLen < 2:
            workPaperLen += 2
        

    def compare_high_1(self, arr, work):
        self.step += 1
        if work[2] >= work[0]:  # high >= low
            self.state = 2
        elif work[2] < work[0]: # high < low
            self.state = 8

    def cal_mid_2(self, arr, work, stack_frames):
        self.step += 1
        global workPaperLen
        work[1] = (work[0] + work[2]) // 2
        if (workPaperLen < 3):
            workPaperLen += 1 
        self.point = work[1] + 3
        stack_frames.append((self.depth, work[0], work[2], work[1], 'push'))
        self.depth += 1
        self.state = 3

    def read_mid_3(self, arr):
        self.step += 1
        self.Mid = arr[self.point]
        self.point = 2   # 指针移到target处
        self.state = 4

    def compare_mid_4(self, arr):
        self.step += 1
        if (self.Mid == arr[self.point]):
            self.state = 7
        elif (self.Mid < arr[self.point]):
            self.state = 5
        elif (self.Mid > arr[self.point]):
            self.state = 6
        
    def update_low_5(self, work):
        self.step += 1
        work[0] = work[1] + 1
        self.state = 1

    def update_high_6(self, work):
        self.step += 1
        work[2] = work[1] - 1
        self.state = 1

    def succes_7(self):
        self.step += 1
        self.output = work[1]
        self.state = 9

    def stop_8(self):
        self.step += 1
        self.output = -1
        self.state = 9

    def return_9(self, stack_frames):
        self.step += 1
        temp_frames = []
        for i, (depth, low, high, mid, operation) in enumerate(stack_frames):
            temp_frames.append((depth, low, high, mid, 'pop'))
        temp_frames.reverse()
        stack_frames.extend(temp_frames)
        self.point = -1
        self.state = -1

    def binary_search(self, arr, work, stack_frames):
        global tape
        while self.state != -1:
            with tape.container():
                st.text(f"输入纸带: {arr}")
                st.text(f"指针: {self.point}")
                st.text(f"工作纸带：{work}")
                st.text(f"输出纸带: {self.output}")
            match self.state:
                case 0:
                    self.read_low_0(arr, work)                
                case 1:
                    self.compare_high_1(arr, work)
                case 2:
                    self.cal_mid_2(arr, work, stack_frames)
                case 3:
                    self.read_mid_3(arr)
                case 4:
                    self.compare_mid_4(arr)
                case 5:
                    self.update_low_5(work)
                case 6:
                    self.update_high_6(work)
                case 7:
                    self.succes_7()
                case 8:
                    self.stop_8()
                case 9:
                    self.return_9(stack_frames)
            # time.sleep(0.5)
        return self.output


# 二分查找，记录栈变化
def binary_search_recursive(arr, target, low, high, stack_frames, depth=0):
    global maxStack, paperLen
    if low > high:
        return -1  # 未找到目标值，返回-1
    mid = (low + high) // 2
    # 栈的push操作
    stack_frames.append((depth, low, high, mid, 'push'))
    maxStack += 1
    workPaperLen += 2
    if arr[mid] == target:
        # 栈的pop操作
        stack_frames.append((depth, low, high, mid, 'pop'))
        return mid
    elif arr[mid] < target:
        result = binary_search_recursive(arr, target, mid + 1, high, stack_frames, depth + 1)
    else:
        result = binary_search_recursive(arr, target, low, mid - 1, stack_frames, depth + 1)
    # 栈的pop操作
    stack_frames.append((depth, low, high, mid, 'pop'))
    return result

# 栈变化仿真
def visualize_stack_changes(stack_frames):
    fig, ax = plt.subplots(figsize=(10, len(stack_frames) * 0.5))  # 新建子图
    stack = []
    y_labels = []
    for i, (depth, low, high, mid, operation) in enumerate(stack_frames):
        if operation == 'push':
            stack.append(f"Depth {depth}: [{low}, {high}] Mid: {mid}")
        elif operation == 'pop' and stack:
            stack.pop()

        ax.clear()
        y_labels = stack.copy()
        for j, label in enumerate(reversed(stack)):
            ax.text(0.5, j, label, ha='center', va='center', fontsize=12, bbox=dict(facecolor='skyblue', alpha=0.5))
        
        ax.set_yticks(range(len(y_labels)))
        ax.set_yticklabels(reversed(y_labels))
        ax.set_xticks([])
        ax.set_ylim(-1, len(stack) + 1)
        ax.set_title("Stack")

        st.pyplot(fig)
        time.sleep(0.5)  # 模拟操作延迟

maxStack = 0
workPaperLen = 0

# Streamlit 界面
st.title("二分查找仿真演示")

# 用户输入
arr = st.text_input("查找列表：", "1,2,3,4,5")
target = st.number_input("目标值：", min_value=1)

# 将用户输入转换为列表
arr = list(map(int, arr.split(',')))

# 判断输入是否合法
if is_increasing(arr) == False:
    st.error(f"查找列表并不单调递增，无法进行二分查找")

# 扩展arr数组使其满足纸带要求
temp = [0]
temp.append(len(arr) - 1)
temp.append(target)
arr = temp + arr

if st.button("开始二分查找："):
    stack_frames = []
    work = [-1, -1, -1]
    output = -1
    # result = binary_search_recursive(arr, target, 0, len(arr) - 1, stack_frames)
    autoMA = AutoMachine()
    
    # 纸带变化过程
    tape = st.empty()

    result = autoMA.binary_search(arr, work, stack_frames)
    if result != -1:
        st.success(f"目标值 {target} 的下标为: {result}")
    else:
        st.error(f"目标值 {target} 未在此列表中找到")
    maxStack = len(stack_frames) // 2
    st.text(f"使用栈空间为 {maxStack}")
    st.text(f"工作纸带长度为 {workPaperLen}")
    st.subheader("二分查找过程中栈的变化：")
    visualize_stack_changes(stack_frames)


# arr = [0, 4, 1, 1, 2, 3, 4, 5]
# work = [-1,-1,-1]
# stack_frames = []
# workPaperLen = 0
# aut = AutoMachine()
# result = aut.binary_search(arr, work, stack_frames)
# print(result)