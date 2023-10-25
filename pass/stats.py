from matplotlib import pyplot as plt
from sys import argv


def make_str_sum(in_tuple):
    if isinstance(in_tuple, str):
        return in_tuple

    out_str = in_tuple[0]
    for i in range(1, len(in_tuple)):
        out_str += "+" + in_tuple[i]

    return out_str


def make_plot(title, instructions, savename):
    fig, ax = plt.subplots(figsize=[16, 8])
    plt.title(title, fontsize=18)
    ax.grid(zorder=0)
    plt.ticklabel_format(style='plain')
    ax.barh(range(len(instructions)), [
            val[1] for val in instructions], align='center', zorder=3)
    ax.set_yticks(range(len(instructions)), [
                  make_str_sum(val[0]) for val in instructions])
    ax.set_xlabel("Frequency", fontsize=15)
    ax.invert_yaxis()
    fig.tight_layout()
    plt.savefig(savename)


def main():
    if len(argv) < 2:
        print(f"Usage: {argv[0]} <trace_file>")
        return

    trace_filename = argv[1]
    outdir = "./"
    instructions = []

    if len(argv) >= 3:
        outdir = argv[2]
        if outdir[-1] != '/':
            outdir += "/"

    with open(trace_filename, "r") as trace_file:
        instructions = trace_file.readlines()

    for i in range(0, len(instructions)):
        instructions[i] = instructions[i].strip()

    unique_instr = {one: instructions.count(one) for one in set(instructions)}

    unique_instr = sorted(unique_instr.items(),
                          key=lambda item: item[1], reverse=True)[0:10]

    make_plot("10 most frequent instructions",
              unique_instr,      outdir + "freq_1.png")


if __name__ == '__main__':
    main()
