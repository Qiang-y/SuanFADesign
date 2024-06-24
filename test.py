import streamlit as st
import matplotlib.pyplot as plt
import time

# 二分查找函数，带堆栈变化记录
def binary_search_recursive(arr, target, low, high, stack_frames, depth=0):
    if low > high:
        return -1  # 未找到目标值，返回-1

    mid = (low + high) // 2

    # 模拟栈的push操作
    stack_frames.append((depth, low, high, mid, 'push'))

    if arr[mid] == target:
        # 模拟栈的pop操作
        stack_frames.append((depth, low, high, mid, 'pop'))
        return mid
    elif arr[mid] < target:
        result = binary_search_recursive(arr, target, mid + 1, high, stack_frames, depth + 1)
    else:
        result = binary_search_recursive(arr, target, low, mid - 1, stack_frames, depth + 1)

    # 模拟栈的pop操作
    stack_frames.append((depth, low, high, mid, 'pop'))
    return result

# 可视化堆栈变化
def visualize_stack_changes(stack_frames):
    fig, ax = plt.subplots(figsize=(10, len(stack_frames) * 0.5))

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
        ax.set_title("Stack Changes in Binary Search")

        st.pyplot(fig)
        time.sleep(0.5)  # 模拟操作延迟

# Streamlit 界面
st.title("Binary Search Visualization")

# 用户输入
arr = st.text_input("Enter a sorted array (comma-separated)", "1,3,5,7,9,11,13,15,17,19")
target = st.number_input("Enter the target value", min_value=1)

# 将用户输入转换为列表
arr = list(map(int, arr.split(',')))

if st.button("Start Binary Search"):
    stack_frames = []
    result = binary_search_recursive(arr, target, 0, len(arr) - 1, stack_frames)

    if result != -1:
        st.success(f"Target value {target} found at index: {result}")
    else:
        st.error(f"Target value {target} not found in the array")

    st.subheader("Stack Changes During Binary Search")
    visualize_stack_changes(stack_frames)
