import { test, expect } from "vitest";
import { toDirection } from "./fields";

test("maps 0 degree to north", () => {
	expect(toDirection(0)).toBe("N")
})

test("maps 45 degree to north-east", () => {
	expect(toDirection(45)).toBe("NE")
})

test("maps 90 degree to east", () => {
	expect(toDirection(90)).toBe("E")
})

test("maps 135 degree to south-east", () => {
	expect(toDirection(135)).toBe("SE")
})

test("maps 180 degree to south", () => {
	expect(toDirection(180)).toBe("S")
})

test("maps 225 degree to south-west", () => {
	expect(toDirection(225)).toBe("SW")
})

test("maps 270 degree to west", () => {
	expect(toDirection(270)).toBe("W")
})

test("maps 315 degree to north-west", () => {
	expect(toDirection(315)).toBe("NW")
})
