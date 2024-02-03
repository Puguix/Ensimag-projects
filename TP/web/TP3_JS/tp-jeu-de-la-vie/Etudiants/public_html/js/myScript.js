const cellSize = 20;
const size = 30;

const life = {
    board: [],
    borderX: function () {
        return (paper.view.size.width - size * cellSize) / 2;
    },
    borderY: function () {
        return (paper.view.size.height - size * cellSize) / 2;
    },
    coords: function (i, j) {
        x = this.borderX() + i * cellSize;
        y = this.borderY() + j * cellSize;
        return [x, y];
    },
    init() {
        for (let i = 0; i < size; i++) {
            this.board[i] = new Array(size);
            for (let j = 0; j < size; j++) {
                this.board[i][j] = new Cell(i, j);
            }
        }
    },
    saveState() {
        for (let i = 0; i < size; i++) {
            for (let j = 0; j < size; j++) {
                this.board[i][j].previousState = this.board[i][j].state;
            }
        }
    },
    getPreviousState(i, j) {
        return this.board[i][j].previousState;
    },

    iterate() {
        this.saveState();
        for (let i = 0; i < size; i++) {
            for (let j = 0; j < size; j++) {
                if (this.board[i][j].shouldLive()) {
                    this.board[i][j].live();
                } else {
                    this.board[i][j].die();
                }
            }
        }
    },
};

class Cell {
    constructor(i, j) {
        this.i = i;
        this.j = j;
        this.state = 0;
        this.previousState = 0;
        this.shape = paper.Path.Circle({
            center: life.coords(this.i, this.j),
            radius: cellSize / 2,
            fillColor: "white",
            strokeColor: "blue",
        });
    }
    live() {
        this.state = 1;
        this.shape.fillColor = "cyan";
    }
    die() {
        this.state = 0;
        this.shape.fillColor = "white";
    }
    shouldLive() {
        let neighborsAlive = 0;
        const neighbors = [
            [this.i - 1, this.j - 1],
            [this.i - 1, this.j],
            [this.i - 1, this.j + 1],
            [this.i, this.j - 1],
            [this.i, this.j + 1],
            [this.i + 1, this.j - 1],
            [this.i + 1, this.j],
            [this.i + 1, this.j + 1],
        ];
        neighbors.forEach((items) => {
            let m = items[0],
                n = items[1];
            if (m >= 0 && m < size && n >= 0 && n < size) {
                neighborsAlive += life.getPreviousState(m, n);
            }
        });
        let bool = false;
        if (
            life.getPreviousState(this.i, this.j) &&
            (neighborsAlive === 2 || neighborsAlive === 3)
        ) {
            bool = true;
        } else if (
            !life.getPreviousState(this.i, this.j) &&
            neighborsAlive === 3
        ) {
            bool = true;
        }
        return bool;
    }
}

function onKeyUp(event) {
    if (event.key == "g") {
        console.log("Step");
        life.iterate();
    }
}

window.addEventListener("keyup", onKeyUp);

window.addEventListener("load", function () {
    let canvas = document.getElementById("myCanvas");
    paper.setup(canvas);

    life.init();

    // Config 1
    // life.board[5][4].live();
    // life.board[5][5].live();
    // life.board[5][6].live();

    // Config 2
    life.board[5][4].live();
    life.board[5][5].live();
    life.board[5][6].live();
    life.board[5][7].live();
    life.board[5][8].live();

    life.board[9][4].live();
    life.board[9][5].live();
    life.board[9][6].live();
    life.board[9][7].live();
    life.board[9][8].live();

    life.board[7][8].live();
    life.board[7][4].live();

    paper.view.setOnFrame(onFrame);
});

function onFrame() {
    life.iterate();
}
