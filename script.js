class ListNode {
    constructor(value) {
        this.value = value;
        this.next = null;
    }
}

class LinkedList {
    constructor() {
        this.head = null;
    }

    insert(value) {
        const newNode = new ListNode(value);
        if (!this.head) {
            this.head = newNode;
            return;
        }
        let current = this.head;
        while (current.next) {
            current = current.next;
        }
        current.next = newNode;
    }

    toArray() {
        const result = [];
        let current = this.head;
        while (current) {
            result.push(current.value);
            current = current.next;
        }
        return result;
    }

    has(value) {
        let current = this.head;
        while (current) {
            if (current.value === value) return true;
            current = current.next;
        }
        return false;
    }
}

document.addEventListener("DOMContentLoaded", function () {
    const setAInput = document.getElementById("set-a");
    const setBInput = document.getElementById("set-b");
    const unionInput = document.getElementById("union");
    const intersectInput = document.getElementById("intersect");

    function parseList(input) {
        const list = new LinkedList();
        input
            .split(",")
            .map(item => item.trim())
            .filter(item => item !== "")
            .forEach(item => list.insert(item));
        return list;
    }

    function updateResults() {
        const listA = parseList(setAInput.value);
        const listB = parseList(setBInput.value);

        // Union
        const unionList = new LinkedList();
        listA.toArray().forEach(item => unionList.insert(item));
        listB.toArray().forEach(item => {
            if (!unionList.has(item)) unionList.insert(item);
        });
        unionInput.value = unionList.toArray().join(", ");

        // Intersection
        const intersectList = new LinkedList();
        listA.toArray().forEach(item => {
            if (listB.has(item)) intersectList.insert(item);
        });
        intersectInput.value = intersectList.toArray().join(", ");
    }

    setAInput.addEventListener("input", updateResults);
    setBInput.addEventListener("input", updateResults);
});
