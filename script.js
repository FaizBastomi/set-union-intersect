class DLLNode {
    constructor(value) {
        this.value = value;
        this.next = null;
        this.prev = null;
    }
}

class DoublyLinkedList {
    constructor() {
        this.head = null;
        this.tail = null;
    }

    insert(value) {
        const newNode = new DLLNode(value);
        if (!this.head) {
            this.head = this.tail = newNode;
            return;
        }
        this.tail.next = newNode;
        newNode.prev = this.tail;
        this.tail = newNode;
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

function unionIterative(listA, listB) {
    const unionList = new DoublyLinkedList();
    const seen = new Set();

    listA.toArray().forEach(item => {
        if (!seen.has(item)) {
            unionList.insert(item);
            seen.add(item);
        }
    });

    listB.toArray().forEach(item => {
        if (!seen.has(item)) {
            unionList.insert(item);
            seen.add(item);
        }
    });

    return unionList;
}

function unionRecursiveHelper(node, unionList, seen) {
    if (!node) return;
    if (!seen.has(node.value)) {
        unionList.insert(node.value);
        seen.add(node.value);
    }
    unionRecursiveHelper(node.next, unionList, seen);
}

function unionRecursive(listA, listB) {
    const unionList = new DoublyLinkedList();
    const seen = new Set();
    unionRecursiveHelper(listA.head, unionList, seen);
    unionRecursiveHelper(listB.head, unionList, seen);
    return unionList;
}

function intersectionIterative(listA, listB) {
    const intersectList = new DoublyLinkedList();
    const seen = new Set();
    listA.toArray().forEach(item => {
        if (listB.has(item) && !seen.has(item)) {
            intersectList.insert(item);
            seen.add(item);
        }
    });
    return intersectList;
}

function intersectionRecursiveHelper(node, listB, intersectList, seen) {
    if (!node) return;
    if (listB.has(node.value) && !seen.has(node.value)) {
        intersectList.insert(node.value);
        seen.add(node.value);
    }
    intersectionRecursiveHelper(node.next, listB, intersectList, seen);
}

function intersectionRecursive(listA, listB) {
    const intersectList = new DoublyLinkedList();
    const seen = new Set();
    intersectionRecursiveHelper(listA.head, listB, intersectList, seen);
    return intersectList;
}

document.addEventListener("DOMContentLoaded", function () {
    const setAInput = document.getElementById("set-a");
    const setBInput = document.getElementById("set-b");
    const unionIterativeInput = document.getElementById("union-iterative");
    const unionRecursiveInput = document.getElementById("union-recursive");
    const intersectIterativeInput = document.getElementById("intersect-iterative");
    const intersectRecursiveInput = document.getElementById("intersect-recursive");
    const uITime = document.getElementById("u-i-time");
    const iITime = document.getElementById("i-i-time");
    const uRTime = document.getElementById("u-r-time");
    const iRTime = document.getElementById("i-r-time");

    function parseDLL(input) {
        const list = new DoublyLinkedList();
        input
            .split(",")
            .map(item => item.trim())
            .filter(item => item !== "")
            .forEach(item => {
                list.insert(item);
            });
        return list;
    }

    function updateResults() {
        const listA = parseDLL(setAInput.value);
        const listB = parseDLL(setBInput.value);

        // Union (iterative + recursive)
        let start = performance.now();
        const unionIter = unionIterative(listA, listB);
        let end = performance.now();
        const uIterTime = (end - start).toFixed(5);

        start = performance.now();
        const unionRec = unionRecursive(listA, listB);
        end = performance.now();
        const uRecTime = (end - start).toFixed(5);

        // Intersection (iterative + recursive)
        start = performance.now();
        const intersectIter = intersectionIterative(listA, listB);
        end = performance.now();
        const iIterTime = (end - start).toFixed(5);

        start = performance.now();
        const intersectRec = intersectionRecursive(listA, listB);
        end = performance.now();
        const iRecTime = (end - start).toFixed(5);

        // Display results
        unionIterativeInput.value = unionIter.toArray().join(", ");
        unionRecursiveInput.value = unionRec.toArray().join(", ");
        intersectIterativeInput.value = intersectIter.toArray().join(", ");
        intersectRecursiveInput.value = intersectRec.toArray().join(", ");
        uITime.textContent = `(${uIterTime}ms)`;
        iITime.textContent = `(${iIterTime}ms)`;
        uRTime.textContent = `(${uRecTime}ms)`;
        iRTime.textContent = `(${iRecTime}ms)`;
    }

    setAInput.addEventListener("input", updateResults);
    setBInput.addEventListener("input", updateResults);
});
