import streamlit as st
import matplotlib.pyplot as plt

# 初始化变量
# weights = [2, 3, 4, 5]
# values = [3, 4, 5, 6]
# capacity = 5

# 用户输入
weights = st.text_input("物品重量：", "2,3,4,5")
values = st.text_input("物品价值：", "3,4,5,6")
capacity = st.number_input("背包容量：", min_value=1)

# 将输入转化为数组
weights = list(map(int, weights.split(',')))
values = list(map(int, values.split(',')))

n = len(weights)
dp = [[-1 for _ in range(capacity + 1)] for _ in range(n)]
steps = 0
stack_depth = 0
max_stack_depth = 0

# 存储每一步的状态变化
dp_snapshots = []
stack_snapshots = []

# 递归函数定义
def solve(i, remaining_capacity, current_stack_depth):
    global steps, stack_depth, max_stack_depth
    steps += 1
    stack_depth = current_stack_depth
    max_stack_depth = max(max_stack_depth, stack_depth)
    
    # 记录当前状态
    dp_snapshots.append([row[:] for row in dp])
    stack_snapshots.append((i, remaining_capacity, current_stack_depth, 'push'))
    
    if i < 0 or remaining_capacity <= 0:
        stack_snapshots.append((i, remaining_capacity, current_stack_depth, 'pop'))
        return 0

    if dp[i][remaining_capacity] != -1:
        stack_snapshots.append((i, remaining_capacity, current_stack_depth, 'pop'))
        return dp[i][remaining_capacity]

    # 选择不取第i个物品
    result = solve(i - 1, remaining_capacity, current_stack_depth + 1)

    # 选择取第i个物品
    if weights[i] <= remaining_capacity:
        result = max(result, solve(i - 1, remaining_capacity - weights[i], current_stack_depth + 1) + values[i])

    dp[i][remaining_capacity] = result
    stack_snapshots.append((i, remaining_capacity, current_stack_depth, 'pop'))
    return result

# 计算结果
max_value = solve(n - 1, capacity, 0)

# 添加剩余的出栈操作
for i in range(n):
    for cap in range(capacity + 1):
        if dp[i][cap] != -1:
            stack_snapshots.append((i, cap, 0, 'pop'))

# 初始化 session_state
if 'step' not in st.session_state:
    st.session_state.step = 0

# Streamlit 页面显示
st.title('01 背包问题 - 备忘录法仿真')
# st.write('物品重量:', weights)
# st.write('物品价值:', values)
# st.write('背包容量:', capacity)
st.write('最大价值:', max_value)
st.write('总步数:', steps)
st.write('最大栈深度:', max_stack_depth)

# 按钮来开始演示过程
if st.button('下一步'):
    st.session_state.step += 1

if st.button('重新开始'):
    st.session_state.step = 0

# 确保步骤不超过快照数
st.session_state.step = min(st.session_state.step, len(dp_snapshots) - 1)

# 显示当前步骤的 DP 表格状态
if st.session_state.step < len(dp_snapshots):
    step = st.session_state.step
    st.subheader(f'Step {step + 1}: DP 表格状态')
    dp_table = ''
    for row in dp_snapshots[step]:
        dp_table += str(row) + '\n'
    st.text(dp_table)
    
    # 显示栈状态
    st.subheader(f'Step {step + 1}: 栈状态')
    current_stack = []
    for i in range(step + 1):
        if stack_snapshots[i][3] == 'push':
            current_stack.append((stack_snapshots[i][0], stack_snapshots[i][1]))
        elif stack_snapshots[i][3] == 'pop' and current_stack:
            current_stack.pop()

    fig, ax = plt.subplots(figsize=(6, 4))
    ax.set_xlim(0, 10)
    ax.set_ylim(-1, len(current_stack))
    ax.set_yticks([])

    for depth, (i, cap) in enumerate(reversed(current_stack)):
        ax.text(5, depth, f'Depth {len(current_stack) - depth - 1}: (i: {i}, cap: {cap})', 
                ha='center', va='center', fontsize=12, bbox=dict(facecolor='lightblue', edgecolor='black', boxstyle='round,pad=0.5'))

    ax.set_title('栈变化过程')
    st.pyplot(fig)
